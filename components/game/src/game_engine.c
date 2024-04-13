/**
 * @file game_engine.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "game_engine.h"
#include "math.h"
#include <time.h>

//---------------------------------- MACROS -----------------------------------
#define PLAYER_STARTING_X            (4U)
#define PLAYER_STARTING_Y            (4U)
#define TORPEDO_DELAY_IN_TIMER_TICKS (2)
#define GAME_EVENT_QUEUE_LEN         (10U)
#define MAP_QUEUE_LEN                (10u)
#define GAME_STATE_QUEUE_LEN         (1u)

#define GAME_LOOP_TIMER_PERIOD_MS   (50U)
#define GAME_LOOP_THREAD_STACK_SIZE (2048U)
#define GAME_LOOP_THREAD_PRIORITY   (tskIDLE_PRIORITY + 2U)

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief Timer  Callback function.
 *
 * @param p_arg - optional timer argument passed to the callback function.
 */
static void _game_loop_timer_callback(TimerHandle_t p_timer);

/**
 * @brief game loop task function
 *
 * @param p_self optional argument passed to the task
 */
void _game_engine_loop_task(void *p_self);

/**
 * @brief static constructor for game engine
 *
 * @param p_self pointer to a game engine object
 * @return true if success
 * @return false otherwise
 */
bool _game_engine_init(game_engine_t *p_self);

/**
 * @brief function for collision checking
 *
 * @param p_self pointer to a game engine object
 * @return true if collision happened
 * @return false otherwise
 */
static bool _game_engine_check_collision(game_engine_t *p_self);

/**
 * @brief send the game state to UI through a queue
 *
 * @param state current game state
 */
static void _game_state_send(game_state_t state);

/**
 * @brief function that fires a torpedo if the player is close enough
 *
 * @param p_self pointer to a game engine
 * @return true if success
 * @return false otherwise
 */
static bool _game_engine_fire_torpedo(game_engine_t *p_self);

/**
 * @brief function that fires a net if the player is close enough
 *
 * @param p_self pointer to a game engine
 * @return true if success
 * @return false otherwise
 */
static bool _game_engine_fire_net(game_engine_t *p_self);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static volatile uint16_t _player_speed_counter = 0;
static uint16_t          _torpedo_delay        = 0;
static bool              b_is_torpedo_available;
static bool              b_is_net_thrown;
static TaskHandle_t      p_task_game_loop_hndl = NULL;
static TimerHandle_t     p_game_loop_timer     = NULL;

//------------------------------- GLOBAL DATA ---------------------------------
QueueHandle_t p_game_event_queue     = NULL;
QueueHandle_t p_map_queue            = NULL;
QueueHandle_t p_game_state_queue     = NULL;
volatile bool b_is_movement_permited = false;
//------------------------------ PUBLIC FUNCTIONS -----------------------------
game_engine_t *game_engine_new()
{
    game_engine_t *p_self = (game_engine_t *)malloc(sizeof(game_engine_t));
    if(p_self)
    {
        if(false == _game_engine_init(p_self))
        {
            free(p_self);
            p_self = NULL;
        }
    }
    return p_self;
}

void game_engine_start(game_engine_t *p_self)
{

    /* start game loop timer */
    if(NULL != p_game_loop_timer)
    {
        if(pdPASS != xTimerStart(p_game_loop_timer, 0))
        {
            printf("The timer could not be set into the Active state.\n");
        }
    }

    /* create a task for game loop */
    if(NULL == p_task_game_loop_hndl)
    {
        BaseType_t task_ret_val;
        task_ret_val = xTaskCreate((TaskFunction_t)_game_engine_loop_task,
                                   "game loop task",
                                   GAME_LOOP_THREAD_STACK_SIZE,
                                   p_self,
                                   GAME_LOOP_THREAD_PRIORITY,
                                   &p_task_game_loop_hndl);

        if((NULL == p_task_game_loop_hndl) || (pdPASS != task_ret_val))
        {
            /* error code here */
            printf("task creation failed.\n");
        }
    }
}

void game_engine_delete(game_engine_t *p_self)
{
    if(NULL == p_self)
    {
        return;
    }
    free(p_self);
    p_self = NULL;

    vTaskDelete(p_task_game_loop_hndl);
    p_task_game_loop_hndl = NULL;
    xTimerStop(p_game_loop_timer, 0);
    xTimerDelete(p_game_loop_timer, 0);
    p_game_loop_timer = NULL;
    vQueueDelete(p_game_event_queue);
    p_game_event_queue = NULL;
    vQueueDelete(p_map_queue);
    p_map_queue = NULL;
    vQueueDelete(p_game_state_queue);
    p_game_state_queue = NULL;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
bool _game_engine_init(game_engine_t *p_self)
{

    bool b_is_valid_init = true;

    /* create player and kraken */
    game_player_init(&p_self->player, PLAYER_STARTING_X, PLAYER_STARTING_Y);

    game_kraken_init(&p_self->kraken, 37, 37);

    /* create a map */
    game_map_update(&p_self->map, p_self->player.base.x, p_self->player.base.y, p_self->kraken.base.x, p_self->kraken.base.y);

    /* set the current game state */
    p_self->state = GAME_IN_PROGRESS;

    /* create a queue for the communication with the UI component */

    p_game_event_queue = xQueueCreate(GAME_EVENT_QUEUE_LEN, sizeof(game_user_input_event_t));

    // Check if queue game_event is created successfully.
    if(NULL == p_game_event_queue)
    {
        printf("Queue error handler.\n");
        b_is_valid_init = false;
    }

    /* CREATE MAP QUEUE */
    if((NULL == p_map_queue))
    {
        p_map_queue = xQueueCreate(MAP_QUEUE_LEN, sizeof(game_map_t));

        if(NULL == p_map_queue)
        {
            printf("Creation of map queue failed.\n");
        }
    }

    /* CREATE GAME STATE QUEUE */
    if((NULL == p_game_state_queue))
    {
        p_game_state_queue = xQueueCreate(GAME_STATE_QUEUE_LEN, sizeof(game_state_t));

        if(NULL == p_game_state_queue)
        {
            printf("Creation of game state queue failed.\n");
        }
    }

    /* create a game timer */
    if((NULL == p_game_loop_timer) && (true == b_is_valid_init))
    {
        p_game_loop_timer = xTimerCreate("game_loop_timer",
                                         (GAME_LOOP_TIMER_PERIOD_MS / portTICK_PERIOD_MS),
                                         pdTRUE,
                                         p_self,
                                         (TimerCallbackFunction_t)_game_loop_timer_callback);

        if(NULL == p_game_loop_timer)
        {
            printf("Handle timer creation error..\n");
            b_is_valid_init = false;
        }
    }
    return b_is_valid_init;
}

void _game_engine_loop_task(void *p_argument)
{
    srand(time(NULL));
    /* handle user input and events */

    game_engine_t *p_self = (game_engine_t *)p_argument;
    b_is_net_thrown       = false;

    for(;;)
    {
        game_user_input_event_t event;

        if(xQueueReceive(p_game_event_queue, &event, 0) == pdPASS)
        {
            // Process the incoming user input event
            switch(event.event_type)
            {
                case PLAYER_MOVE_EVENT:
                    // Handle player movement event
                    game_object_move((&p_self->player), event.delta_x, event.delta_y);
                    game_map_update(
                        &p_self->map, p_self->player.base.x, p_self->player.base.y, p_self->kraken.base.x, p_self->kraken.base.y);

                    if(true == _game_engine_check_collision(p_self))
                    {
                        /* handle collision */
                        b_is_net_thrown = false;
                        _game_state_send(GAME_LOST);
                    }
                    _player_speed_counter = 0;
                    break;

                case KRAKEN_MOVE_EVENT:
                    if(false == b_is_net_thrown)
                    {
                        game_object_move(&p_self->kraken, event.delta_x, event.delta_y);
                        game_map_update(
                            &p_self->map, p_self->player.base.x, p_self->player.base.y, p_self->kraken.base.x, p_self->kraken.base.y);
                    }

                    if(true == _game_engine_check_collision(p_self))
                    {
                        /* handle collision */
                        b_is_net_thrown = false;
                        _game_state_send(GAME_LOST);
                    }
                    break;

                    // Handle torpedo firing event
                case TORPEDO_FIRING_EVENT:
                    if((true == b_is_torpedo_available) && (true == _game_engine_fire_torpedo(p_self)))
                    {
                        b_is_net_thrown = false;
                        _game_state_send(GAME_WIN);
                    }

                    break;
                case NET_FIRING_EVENT:
                    if(true == _game_engine_fire_net(p_self))
                    {
                        printf("The net is thrown\n");
                    }

                    break;
            }
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

static bool _game_engine_fire_torpedo(game_engine_t *p_self)
{
    bool b_is_torpedo_successful = false;
    if(DISTANCE_P_2_K(p_self->map) <= 8)
    {
        /* check if the net is fired */
        if(true == b_is_net_thrown)
        {
            /* kraken killed -> game win */
            b_is_torpedo_successful = true;
        }
        /* implement a 30% chance */
        int random_number = rand() % 10;
        if(random_number < 3)
        {
            b_is_torpedo_successful = true;
        }
    }
    p_self->player.no_of_torpedos--;
    _torpedo_delay = 0;

    return b_is_torpedo_successful;
}

static bool _game_engine_fire_net(game_engine_t *p_self)
{
    if(DISTANCE_P_2_K(p_self->map) <= 10)
    {

        b_is_net_thrown = true;
        p_self->player.no_of_nets--;
    }
    return b_is_net_thrown;
}

static bool _game_engine_check_collision(game_engine_t *p_self)
{

    return (DISTANCE(p_self->map.player_x, p_self->map.player_y, p_self->map.kraken_x, p_self->map.kraken_y) <= 6) ? true : false;
}

static void _game_loop_timer_callback(TimerHandle_t p_timer)
{
    game_engine_t *p_self = (game_engine_t *)pvTimerGetTimerID(p_timer);

    /* call it every TIMER_PERIOD_MS ms and increment the counters
     * player is allowed to move when the counter is at 1000/(player.speed * TIMER_PERIOD_MS)
     * when the player moves, the counter resets to 0.
     * for example, player.speed is 1, TIMER_PERIOD_MS is 50 ms, so when the counter hits 20
     * the player can move again. That way the player is moving 1 move per second at best.
     */
    if(_player_speed_counter >= (1000 / (PLAYER_SPEED * GAME_LOOP_TIMER_PERIOD_MS)))
    {

        /* give approval for movement */
        b_is_movement_permited = true;

        _player_speed_counter = 0;
    }
    else
    {
        _player_speed_counter++;
    }

    if(_torpedo_delay >= TORPEDO_DELAY_IN_TIMER_TICKS)
    {
        b_is_torpedo_available = true;
    }
    else
    {
        _torpedo_delay++;
    }

    // /* render with every timer count */
    if(xQueueSend(p_map_queue, (void *)&p_self->map, (TickType_t)0) != pdPASS)
    {
        /* Failed to post the message */
    }
}

static void _game_state_send(game_state_t state)
{
    if(xQueueSend(p_game_state_queue, (void *)&state, (TickType_t)0) != pdPASS)
    {
        /* Failed to post the message */
        printf("Failed to send the game state\n");
    }
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
