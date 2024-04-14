/**
 * @file game.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "game.h"
#include "math.h"
#include <time.h>

//---------------------------------- MACROS -----------------------------------
#define GAME_EVENT_T_QUEUE_LEN         (10U)
#define MAP_QUEUE_LEN                (10u)
#define GAME_STATE_QUEUE_LEN         (1u)

#define GAME_LOOP_THREAD_STACK_SIZE (2048U)
#define GAME_LOOP_THREAD_PRIORITY   (tskIDLE_PRIORITY + 2U)

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
// /**
//  * @brief Timer  Callback function.
//  *
//  * @param p_arg - optional timer argument passed to the callback function.
//  */
// static void _game_loop_timer_callback(TimerHandle_t p_timer);

/**
 * @brief game loop task function
 *
 * @param p_self optional argument passed to the task
 */
void _game_loop_task(void *p_self);

/**
 * @brief static constructor for game engine
 *
 * @param p_self pointer to a game engine object
 * @return true if success
 * @return false otherwise
 */
bool _game_init(game_t *p_self);


/**
 * @brief send the game state to UI through a queue
 *
 * @param state current game state
 */
static void _game_state_send(game_state_t state);


//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TaskHandle_t      p_task_game_loop_hndl = NULL;
// static TimerHandle_t     p_game_loop_timer     = NULL;

//------------------------------- GLOBAL DATA ---------------------------------
QueueHandle_t p_game_event_queue     = NULL;
// QueueHandle_t p_map_queue            = NULL;
QueueHandle_t p_game_state_queue     = NULL;
volatile bool b_is_movement_permited = false;
//------------------------------ PUBLIC FUNCTIONS -----------------------------
game_t *game_new()
{
    game_t *p_self = (game_t *)malloc(sizeof(game_t));
    if(p_self)
    {
        if(false == _game_init(p_self))
        {
            free(p_self);
            p_self = NULL;
        }
    }
    return p_self;
}

void game_start(game_t *p_self)
{

    // /* start game loop timer */
    // if(NULL != p_game_loop_timer)
    // {
    //     if(pdPASS != xTimerStart(p_game_loop_timer, 0))
    //     {
    //         printf("The timer could not be set into the Active state.\n");
    //     }
    // }

    /* create a task for game loop */
    if(NULL == p_task_game_loop_hndl)
    {
        BaseType_t task_ret_val;
        task_ret_val = xTaskCreate((TaskFunction_t)_game_loop_task,
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

    p_self->state = GAME_IN_PROGRESS;
}

bool check_if_end(game_t *p_self) {
    // check if three in a row

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((p_self->board.pos[i + 3 * 0] == 1 && p_self->board.pos[i + 3 * 1] == 1 && p_self->board.pos[i + 3 * 2] == 1) ||
            (p_self->board.pos[0 + 3 * i] == 1 && p_self->board.pos[1 + 3 * i] == 1 && p_self->board.pos[2 + 3 * i] == 1)) {
            printf("ravno\n");
            return true;
        }

        if ((p_self->board.pos[i + 3 * 0] == 0 && p_self->board.pos[i + 3 * 1] == 0 && p_self->board.pos[i + 3 * 2] == 0) ||
            (p_self->board.pos[0 + 3 * i] == 0 && p_self->board.pos[1 + 3 * i] == 0 && p_self->board.pos[2 + 3 * i] == 0)) {
            printf("ravno\n");
            return true;
        }
    }
    
    if ((p_self->board.pos[0] == 1 && p_self->board.pos[4] == 1 && p_self->board.pos[8] == 1) ||
        (p_self->board.pos[2] == 1 && p_self->board.pos[4] == 1 && p_self->board.pos[6] == 1)) {
        printf("dijagonala\n");
        return true;
    }

    if ((p_self->board.pos[0] == 0 && p_self->board.pos[4] == 0 && p_self->board.pos[8] == 0) ||
        (p_self->board.pos[2] == 0 && p_self->board.pos[4] == 0 && p_self->board.pos[6] == 0)) {
        printf("dijagonala\n");
        return true;
    }
    
    printf("nope\n");
    return false;

}

bool check_if_draw(game_t *p_self) {
    for (int i = 0; i < 9; i++) {
        if (p_self->board.pos[i] == -1) return false;
    }
    return !check_if_end(p_self);
}



void game_delete(game_t *p_self)
{
    if(NULL == p_self)
    {
        return;
    }
    free(p_self);
    p_self = NULL;

    vTaskDelete(p_task_game_loop_hndl);
    p_task_game_loop_hndl = NULL;
    // xTimerStop(p_game_loop_timer, 0);
    // xTimerDelete(p_game_loop_timer, 0);
    // p_game_loop_timer = NULL;
    vQueueDelete(p_game_event_queue);
    p_game_event_queue = NULL;
    // vQueueDelete(p_map_queue);
    // p_map_queue = NULL;
    vQueueDelete(p_game_state_queue);
    p_game_state_queue = NULL;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
bool _game_init(game_t *p_self)
{

    bool b_is_valid_init = true;


    /* set the current game state */
    p_self->state = GAME_IN_PROGRESS;

    /* create a queue for the communication with the UI component */

    p_game_event_queue = xQueueCreate(GAME_EVENT_T_QUEUE_LEN, sizeof(game_move_event_t));

    // Check if queue game_event_t is created successfully.
    if(NULL == p_game_event_queue)
    {
        printf("Queue error handler.\n");
        b_is_valid_init = false;
    }

    // /* CREATE MAP QUEUE */
    // if((NULL == p_map_queue))
    // {
    //     p_map_queue = xQueueCreate(MAP_QUEUE_LEN, sizeof(game_map_t));

    //     if(NULL == p_map_queue)
    //     {
    //         printf("Creation of map queue failed.\n");
    //     }
    // }

    /* CREATE GAME STATE QUEUE */
    if((NULL == p_game_state_queue))
    {
        p_game_state_queue = xQueueCreate(GAME_STATE_QUEUE_LEN, sizeof(game_state_t));

        if(NULL == p_game_state_queue)
        {
            printf("Creation of game state queue failed.\n");
        }
    }

    // /* create a game timer */
    // if((NULL == p_game_loop_timer) && (true == b_is_valid_init))
    // {
    //     p_game_loop_timer = xTimerCreate("game_loop_timer",
    //                                      (GAME_LOOP_TIMER_PERIOD_MS / portTICK_PERIOD_MS),
    //                                      pdTRUE,
    //                                      p_self,
    //                                      (TimerCallbackFunction_t)_game_loop_timer_callback);

    //     if(NULL == p_game_loop_timer)
    //     {
    //         printf("Handle timer creation error..\n");
    //         b_is_valid_init = false;
    //     }
    // }

    board_init(&p_self->board);
    return b_is_valid_init;
}

void _game_loop_task(void *p_argument)
{

    game_t *p_self = (game_t *)p_argument;

    for(;;)
    {
        game_move_event_t event;

        if(xQueueReceive(p_game_event_queue, &event, 500) == pdPASS)
        {
            // Process the incoming user input event
            
            p_self->board.pos[event.posX] = 1;
            p_self->board.pos[event.posO] = 0;

            // check end
            check_if_end(p_self);
        }


        // vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}


// static void _game_loop_timer_callback(TimerHandle_t p_timer)
// {
//     game_t *p_self = (game_t *)pvTimerGetTimerID(p_timer);


//     // /* render with every timer count */
//     if(xQueueSend(p_map_queue, (void *)&p_self->map, (TickType_t)0) != pdPASS)
//     {
//         /* Failed to post the message */
//     }
// }

static void _game_state_send(game_state_t state)
{
    if(xQueueSend(p_game_state_queue, (void *)&state, (TickType_t)0) != pdPASS)
    {
        /* Failed to post the message */
        printf("Failed to send the game state\n");
    }
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
