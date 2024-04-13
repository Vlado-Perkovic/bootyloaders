// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: SquareLine_Project

#include "ui.h"

#include "wifi.h"
#include "telemetry.h"
#include "led.h"
#include "button.h"
#include "joystick.h"
#include "game_engine.h"
#include "math.h"
#include <string.h>

//---------------------------------- MACROS -----------------------------------

#define MAIN_THREAD_STACK_SIZE   (4096u)
#define MAIN_THREAD_PRIORITY     (5u)
#define BUTTON_THREAD_STACK_SIZE (1024U)
#define BUTTON_THREAD_PRIORITY   (5u)

#define TELEMETRY_PERIOD_MS (5000)

#define NO_TIMEOUT (UINT_MAX)

#define BUTTON_QUEUE_LEN (10u)

#define GRID_OFFSET       (20)
#define GRID_SCALE        (5)
#define MAP_OFFSET_X_AXIS (-163)
#define MAP_OFFSET_Y_AXIS (-118)
//------------------------- STATIC DATA & CONSTANTS ---------------------------
static QueueHandle_t  p_button_queue    = NULL;
static game_engine_t *p_game            = NULL;
static lv_group_t    *p_weapons_group   = NULL;
static game_state_t   state             = GAME_IN_PROGRESS;
static bool           b_is_provisioning = false;
static bool           b_is_light_on     = false;
static TimerHandle_t  p_telemetry_timer = NULL;
static char           json[100];

//------------------------------- GLOBAL DATA ---------------------------------
// extern QueueHandle_t p_game_event_queue;
// extern volatile bool b_is_movement_permited;
// extern QueueHandle_t p_map_queue;
// extern QueueHandle_t p_game_state_queue;


// -----------------------Private Function Definitions-----------------------
/**
 * @brief private function for the main task
 *
 * It deals with all the logic handling, interrupts send signals
 * through a queue which this task handles appropriately
 */
static void _main_task();

static void _telemetry_timer_callback(TimerHandle_t p_timer);

static void _telemetry_server_callback(const char *p_msg);



// -----------------------Private Functions---------------------------------
void wifi_on_status_change_callback(wifi_connection_status_t new_status)
{
    if(WIFI_CONNECTION_STATUS_CONNECTED == new_status)
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI CONNECTED");
                printf("con\n");

        b_is_provisioning = false;
        /* when connected, init the telemetry  and start the timer */
        telemetry_init();

        if(NULL != p_telemetry_timer)
        {
            if(pdPASS != xTimerStart(p_telemetry_timer, 0))
            {
                printf("The timer could not be set into the Active state.\n");
            }
        }
    }

    if(WIFI_CONNECTION_STATUS_DISCONNECTED == new_status)
    {
        lv_label_set_text(ui_WifiAvailability, "CONNECTION FAILED");
                printf("con fail\n");

        b_is_provisioning = false;
    }
}

static void _main_task()
{
	// Your code here
    for(;;) {
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void btn1_clicked(lv_event_t * e)
{
	// Your code here
}

void ui_setup(lv_event_t * e)
{
    /* SETUP ALL LEDS */
    if((LED_ERR_NONE != led_init(LED_RED)) || (LED_ERR_NONE != led_init(LED_GREEN)) || (LED_ERR_NONE != led_init(LED_BLUE)))
    {
        printf("An error has occured with led init.\n");
    }

    /* SETUP JOYSTICK */
    if((JOYSTICK_ERR_NONE != joystick_init(JOYSTICK_1)))
    {
        printf("An error has occured with joystick init.\n");
    }

    /* wifi init upon startup */
    wifi_register_on_status_changed(&wifi_on_status_change_callback);
    wifi_init();

     /* SETUP TELEMETRY CALLBACK */
    telemetry_driver_register_on_new_message(&_telemetry_server_callback);

    /* CREATE MAIN TASK */
    if(pdPASS != xTaskCreate(&_main_task, "main task", MAIN_THREAD_STACK_SIZE, NULL, MAIN_THREAD_PRIORITY, NULL))
    {
        printf("Creation of user interface task failed.\n");
    }

    /* create a telemetry timer for sending data to basecamp */
    if((NULL == p_telemetry_timer))
    {
        p_telemetry_timer = xTimerCreate("p_telemetry_timer",
                                         (TELEMETRY_PERIOD_MS / portTICK_PERIOD_MS),
                                         pdTRUE,
                                         NULL,
                                         (TimerCallbackFunction_t)_telemetry_timer_callback);

        if(NULL == p_telemetry_timer)
        {
            printf("Handle timer creation error..\n");
        }
    }

    printf("ui setup done!\n");
            lv_label_set_text(ui_WifiAvailability, "BOK");

}

void start_provision(lv_event_t * e)
{
	// Your code here
    /* TOGGLE PROVISION */
    if(false == b_is_provisioning)
    {
        b_is_provisioning = true;
        wifi_provision(WIFI_PROV_METHOD_BLE);
        lv_label_set_text(ui_WifiAvailability, "WIFI PROVISIONING");
                printf("wifi prov\n");

    }
    else
    {
        wifi_provision_stop();
        b_is_provisioning = false;
        lv_label_set_text(ui_WifiAvailability, "PROV CANCELED");
                printf("prov can\n");

    }

}

void connect_to_wifi(lv_event_t * e)
{
	// Your code here
        wifi_connect();

}

void ui_events_is_wifi_available(lv_event_t * e)
{
	// Your code here
    /* update the status bar */
    bool b_is_provisioned = false;
    if(true == wifi_is_wifi_connected())
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI CONNECTED");
        printf("CONNECTED\n");
    }
    else if(WIFI_OK != wifi_is_provisioned(&b_is_provisioned) || (false == b_is_provisioned))
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI NOT AVAILABLE");
                printf("not a\n");

    }
    else
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI AVAILABLE");
                printf("a\n");

    }
}

static void _telemetry_timer_callback(TimerHandle_t p_timer)
{

    /* Timer formats and sends the current location and diver name to the basecamp */
    // const char *name = "Vlado";
    // uint8_t     x    = 0;
    // uint8_t     y    = 0;
    // if(NULL != p_game)
    // {
    //     x = p_game->map.player_x;
    //     y = p_game->map.player_y;
    // }
    // // Format JSON using snprintf
    // snprintf(json,
    //          sizeof(json),
    //          "{"
    //          "  \"temp\": %d,"
    //          "  \"hum\": %d,"
    //          "  \"acc\": [\"x\": %f, \"y\": %f, \"z\": %f]"
    //          "}",
    //          temp,
    //          hum,
    //          x, y, z);
    // telemetry_connection_status_update(json);
}

static void _telemetry_server_callback(const char *p_msg)
{
    /* set the starting position at the coordinates
        {
            "Monster": "Kraken",
            "position": [
            12,         ^
            25          |
            ]          here is the start
        }
    */
    // const char *start = strstr(p_msg, "[");

    // int x, y;

    // game_user_input_event_t event;
    // event.event_type = KRAKEN_MOVE_EVENT;
    // if(start != NULL)
    // {
    //     /* try to parse the two coordinates */
    //     if(sscanf(start, "[%d,%d]", &x, &y) == 2)
    //     {
    //         event.delta_x = x;
    //         event.delta_y = y;
    //         if(NULL != p_game_event_queue)
    //         {
    //             _ui_send_event_to_game_engine(event);
    //         }
    //     }
    // }
    // else
    // {
    //     printf("Position not found in the message.\n");
    // }
}

