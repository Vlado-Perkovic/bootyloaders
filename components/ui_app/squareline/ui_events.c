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
// #include "game_engine.h"
#include "math.h"
#include <string.h>
#include "sht3x.h"
#include "esp_log.h"
#include "game.h"

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

#define UART_STACK_SIZE (4096)

#define JSON_OFFSET (28)

static const char *MAIN_TAG    = "main";
static const char *SENSORS_TAG = "sensors";

char scale = SCALE_CELCIUS;
//------------------------- STATIC DATA & CONSTANTS ---------------------------
static QueueHandle_t p_button_queue          = NULL;
static game_t       *p_game                  = NULL;
static lv_group_t   *p_weapons_group         = NULL;
static game_state_t  state                   = GAME_IN_PROGRESS;
static bool          b_is_provisioning       = false;
static bool          b_is_light_on           = false;
static TaskHandle_t  p_task_measurement_hndl = NULL;
static TimerHandle_t p_telemetry_timer       = NULL;
static char          json[100];
static char          measurements[50];
float                temperature = 0.0;
float                humidity    = 0.0;

uint8_t adjust_offset;

bool is_my_turn  = false;
bool player_is_X = false;
char msg[100];

//------------------------------- GLOBAL DATA ---------------------------------
extern QueueHandle_t p_game_event_queue;
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
static void _measurement_loop_task();

static void _ui_send_event_to_game_engine(game_move_event_t event);

static void _send_move();

void _exit_game();

void insertAfterSubstring(char *str, const char *substring, const char *insertStr)
{
    // Find the position of the substring
    char *pos = strstr(str, substring);
    if(pos != NULL)
    {
        // Calculate the position to insert after
        int insertPos = pos - str + strlen(substring) - 1;

        // Make space for the new string
        memmove(str + insertPos + strlen(insertStr), str + insertPos, strlen(str) - insertPos + 1);

        // Insert the new string
        strncpy(str + insertPos, insertStr, strlen(insertStr));

        pos       = strstr(str, "device");
        insertPos = pos - str + 6 - 1;
    }
    else
    {
        printf("Substring not found.\n");
    }
}

void replaceWord(char *str, const char *oldWord, const char *newWord)
{
    char *pos = strstr(str, oldWord); // Find the position of the old word
    if(pos != NULL)
    {
        int wordLen = strlen(oldWord);  // Length of the old word
        strncpy(pos, newWord, wordLen); // Copy new word over old word
    }
    else
    {
        printf("Old word not found.\n");
    }
}

// -----------------------Private Functions---------------------------------
void wifi_on_status_change_callback(wifi_connection_status_t new_status)
{
    if(WIFI_CONNECTION_STATUS_CONNECTED == new_status)
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI CONNECTED");
        printf("con\n");
        led_on(LED_GREEN);

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
                led_off(LED_GREEN);


        b_is_provisioning = false;
    }
}

static void _main_task()
{
    xTaskCreate((TaskFunction_t)_measurement_loop_task, "measurement task", 1024 * 4, NULL, 9, &p_task_measurement_hndl);

    // ----------------------------

    for(;;)
    {
        // if ((p_game != NULL) && (p_game->state != GAME_IN_PROGRESS)) {
        //     _exit_game();
        // }
        // _ui_send_event_to_game_engine(ev);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void btn1_clicked(lv_event_t *e)
{
    // Your code here
}

void ui_setup(lv_event_t *e)
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
}

void start_provision(lv_event_t *e)
{
    // Your code here
    /* TOGGLE PROVISION */
    if(false == b_is_provisioning)
    {
        b_is_provisioning = true;
        wifi_provision(WIFI_PROV_METHOD_BLE);
        lv_label_set_text(ui_WifiAvailability, "WIFI PROVISIONING");
                led_on(LED_RED);
                led_off(LED_GREEN);


    }
    else
    {
        wifi_provision_stop();
        b_is_provisioning = false;
        lv_label_set_text(ui_WifiAvailability, "PROV CANCELED");
                led_off(LED_RED);
                        led_off(LED_GREEN);


    }
}

void connect_to_wifi(lv_event_t *e)
{
    // Your code here
    wifi_connect();
}

void ui_events_is_wifi_available(lv_event_t *e)
{
    // Your code here
    /* update the status bar */
    bool b_is_provisioned = false;
    if(true == wifi_is_wifi_connected())
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI CONNECTED");
                led_on(LED_GREEN);

    }
    else if(WIFI_OK != wifi_is_provisioned(&b_is_provisioned) || (false == b_is_provisioned))
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI NOT AVAILABLE");
                led_off(LED_GREEN);

    }
    else
    {
        lv_label_set_text(ui_WifiAvailability, "WIFI AVAILABLE");
                led_off(LED_GREEN);

    }
}

static void _telemetry_timer_callback(TimerHandle_t p_timer)
{

    /* Timer formats and sends the current location and diver name to the basecamp */
    const char *name = "Vlado";
    float       x    = 69.0;
    float       y    = 69.0;
    float       z    = 69.0;

    // Format JSON using snprintf
    snprintf(json,
             sizeof(json),
             "{"
             "\"temp\":%d,"
             "\"hum\":%d,"
             "\"acc\":{\"x\":%f,\"y\":%f,\"z\":%f}"
             "}",
             (int)temperature,
             (int)humidity,
             x,
             y,
             z);
    telemetry_connection_status_update(json);
}

static void _send_move()
{
    const char *name = "Vlado";
    float       x    = 69.0;
    float       y    = 69.0;
    float       z    = 69.0;

    // Format JSON using snprintf
    snprintf(json,
             sizeof(json),
             "{"
             "\"indexX\":[],"
             "\"indexO\":[],"
             "\"turn\":{\"x\":\"server\""
             "}");
}
static void _telemetry_server_callback(const char *p_msg)
{

    game_move_event_t event;
    memset(msg, 0, 100);
    strncpy(msg, p_msg, 99);
    msg[99] = '\0';

    led_custom_pattern(LED_BLUE, 2000);

    const char *start = strstr(msg, "]");

    int x = -1;
    // event.event_type = KRAKEN_MOVE_EVENT;
    if(start != NULL)
    {
        /* try to parse the two coordinates */
        if(sscanf(start - 1, "%d", &x) == 1)
        {

            printf("%d\n", x);
            event.posX = x;
        }
    }
    start = strstr(msg + JSON_OFFSET - adjust_offset, "]");
    x     = -1;

    // event.event_type = KRAKEN_MOVE_EVENT;
    if(start != NULL)
    {
        /* try to parse the two coordinates */
        if(sscanf(start - 1, "%d", &x) == 1)
        {

            printf("%d\n", x);
            event.posO = x;
        }
    }

    start = strstr(msg + JSON_OFFSET - adjust_offset, "turn");

    if((start != NULL) && (p_game->state == GAME_IN_PROGRESS))
    {
        char turn[6 + 1];
        strncpy(turn, start + 8, 6);
        turn[6] = '\0';
        printf("%s\n", turn);
        if((strncmp(turn, "device", 7) == 0))
        {
            printf("Server govori da je nas red\n");
            // _ui_send_event_to_game_engine(event);
            if(player_is_X)
            {
                p_game->board.pos[event.posO] = 0;
                // printf("event poso: %d\n", event.posO);

                switch(event.posO)
                {
                    case 0:
                        lv_label_set_text(ui_znak0, "O");

                        break;
                    case 1:
                        lv_label_set_text(ui_znak1, "O");

                        break;
                    case 2:
                        lv_label_set_text(ui_znak2, "O");

                        break;
                    case 3:
                        lv_label_set_text(ui_znak3, "O");

                        break;
                    case 4:
                        lv_label_set_text(ui_znak4, "O");

                        break;
                    case 5:
                        lv_label_set_text(ui_znak5, "O");

                        break;
                    case 6:
                        lv_label_set_text(ui_znak6, "O");

                        break;
                    case 7:
                        lv_label_set_text(ui_znak7, "O");

                        break;
                    case 8:
                        lv_label_set_text(ui_znak8, "O");

                        break;

                    default:
                        break;
                }
            }
            else
            {
                p_game->board.pos[event.posX] = 1;
                // printf("event posx: %d\n", event.posX);
                switch(event.posX)
                {
                    case 0:
                        lv_label_set_text(ui_znak0, "X");

                        break;
                    case 1:
                        lv_label_set_text(ui_znak1, "X");

                        break;
                    case 2:
                        lv_label_set_text(ui_znak2, "X");

                        break;
                    case 3:
                        lv_label_set_text(ui_znak3, "X");

                        break;
                    case 4:
                        lv_label_set_text(ui_znak4, "X");

                        break;
                    case 5:
                        lv_label_set_text(ui_znak5, "X");

                        break;
                    case 6:
                        lv_label_set_text(ui_znak6, "X");

                        break;
                    case 7:
                        lv_label_set_text(ui_znak7, "X");

                        break;
                    case 8:
                        lv_label_set_text(ui_znak8, "X");

                        break;

                    default:
                        break;
                }
            }
            is_my_turn = true;
            lv_label_set_text(ui_Label6, "Your turn!");

            replaceWord(msg, "device", "server");

            if(check_if_end(p_game))
            {
                p_game->state = GAME_LOST;
                lv_label_set_text(ui_Label6, "GAME LOST :(");
            }
        }
    }
}

static void _measurement_loop_task()
{
    i2c_config_t i2c_config = { .mode             = I2C_MODE_MASTER,
                                .sda_io_num       = I2C_MASTER_SDA,
                                .sda_pullup_en    = GPIO_PULLUP_ENABLE,
                                .scl_io_num       = I2C_MASTER_SCL,
                                .scl_pullup_en    = GPIO_PULLUP_ENABLE,
                                .master.clk_speed = I2C_MASTER_FREQ_HZ };

    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, i2c_config.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));

    esp_log_level_set(SENSORS_TAG, ESP_LOG_INFO);

#if defined(SENSORS_SCALE_F)
    scale = SCALE_FAHRENHEIT;
#elif defined(SENSORS_SCALE_K)
    scale = SCALE_KELVIN;
#endif

    vTaskDelay(100 / portTICK_PERIOD_MS);

    for(;;)
    {

        // zaseban task
        sht3x_start_periodic_measurement();

        sht3x_sensors_values_t sensors_values = { .temperature = 0x00, .humidity = 0x00 };
        vTaskDelay(100 / portTICK_PERIOD_MS);

        if(sht3x_read_measurement(&sensors_values) != ESP_OK)
        {
            ESP_LOGE(SENSORS_TAG, "Sensors read measurement error!");
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);

        temperature = sensors_values.temperature;
        humidity    = sensors_values.humidity;

#if defined(SENSORS_SCALE_F)
        temperature = FAHRENHEIT(temperature);
#elif defined(SENSORS_SCALE_K)
        temperature = KELVIN(temperature);
#endif

        ESP_LOG_BUFFER_HEX_LEVEL(SENSORS_TAG, &sensors_values, sizeof(sensors_values), ESP_LOG_DEBUG);

        sht3x_stop_periodic_measurement();

        ESP_LOGI(SENSORS_TAG, "Temperature %2.1f °%c - Humidity %2.1f%%", temperature, scale, humidity);

        snprintf(measurements, sizeof(measurements), "%d deg C", (int)temperature);

        lv_label_set_text(ui_tempLabel, measurements);
        snprintf(measurements, sizeof(measurements), "%d percent", (int)humidity);
        lv_label_set_text(ui_accLabel, measurements);
        snprintf(measurements, sizeof(measurements), "x: %d\ny: %d\nz: %d", 0, 0, 0);
        lv_label_set_text(ui_humidLabel, measurements);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

static void _ui_send_event_to_game_engine(game_move_event_t event)
{
    if(NULL != p_game_event_queue)
    {

        if(xQueueSend(p_game_event_queue, (void *)&event, (TickType_t)0) != pdPASS)
        {
            /* Failed to post the message */
            printf("FAILED TO POST A MESSAGE\n");
        }
    }
}

void poz0callback(lv_event_t *e)
{
    // Your code here
    printf("%d\n", p_game->board.pos[0]);

    if((p_game->board.pos[0] != -1) || (is_my_turn == false) || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak0, "X");

        p_game->board.pos[0] = 1;
        insertAfterSubstring(msg, "]", ",0");
    }
    else
    {
        lv_label_set_text(ui_znak0, "O");
        p_game->board.pos[0] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "0");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",0");
        }
    }

    telemetry_send("WES/Neptune/game", msg);

    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }

    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz1callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[1]);

    if((p_game->board.pos[1] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak1, "X");

        p_game->board.pos[1] = 1;
        insertAfterSubstring(msg, "]", ",1");
    }
    else
    {
        lv_label_set_text(ui_znak1, "O");
        p_game->board.pos[1] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "1");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",1");
        }
    }

    telemetry_send("WES/Neptune/game", msg);
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz2callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[2]);

    if((p_game->board.pos[2] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak2, "X");

        p_game->board.pos[2] = 1;
        insertAfterSubstring(msg, "]", ",2");
    }
    else
    {
        lv_label_set_text(ui_znak2, "O");
        p_game->board.pos[2] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "2");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",2");
        }
    }

    telemetry_send("WES/Neptune/game", msg);
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz3callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[3]);

    if((p_game->board.pos[3] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak3, "X");

        p_game->board.pos[3] = 1;
        insertAfterSubstring(msg, "]", ",3");
    }
    else
    {
        lv_label_set_text(ui_znak3, "O");
        p_game->board.pos[3] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "3");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",3");
        }
    }
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    telemetry_send("WES/Neptune/game", msg);

    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz4callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[4]);

    if((p_game->board.pos[4] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak4, "X");

        p_game->board.pos[4] = 1;
        insertAfterSubstring(msg, "]", ",4");
    }
    else
    {
        lv_label_set_text(ui_znak4, "O");
        p_game->board.pos[4] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "4");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",4");
        }
    }

    telemetry_send("WES/Neptune/game", msg);
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz5callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[5]);

    if((p_game->board.pos[5] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak5, "X");

        p_game->board.pos[5] = 1;
        insertAfterSubstring(msg, "]", ",5");
    }
    else
    {
        lv_label_set_text(ui_znak5, "O");
        p_game->board.pos[5] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "5");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",5");
        }
    }

    telemetry_send("WES/Neptune/game", msg);
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz6callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[6]);

    if((p_game->board.pos[6] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak6, "X");

        p_game->board.pos[6] = 1;
        insertAfterSubstring(msg, "]", ",6");
    }
    else
    {
        lv_label_set_text(ui_znak6, "O");
        printf("napisao O\n");
        p_game->board.pos[6] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;
        char *pos            = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        printf("napisao O\n");

        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "6");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",6");
        }
    }

    telemetry_send("WES/Neptune/game", msg);
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz7callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[7]);

    if((p_game->board.pos[7] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak7, "X");

        p_game->board.pos[7] = 1;
        insertAfterSubstring(msg, "]", ",7");
    }
    else
    {
        lv_label_set_text(ui_znak7, "O");
        p_game->board.pos[7] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "7");
        }
        else
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",7");
        }
    }

    telemetry_send("WES/Neptune/game", msg);
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void poz8callback(lv_event_t *e)
{
    printf("%d\n", p_game->board.pos[8]);

    if((p_game->board.pos[8] != -1) || !is_my_turn || (p_game->state != GAME_IN_PROGRESS))
        return;

    if(player_is_X)
    {
        lv_label_set_text(ui_znak8, "X");

        p_game->board.pos[8] = 1;
        insertAfterSubstring(msg, "]", ",8");
    }
    else
    {
        lv_label_set_text(ui_znak8, "O");
        p_game->board.pos[8] = 0;
        adjust_offset        = (strlen(msg) > 50) ? 0 : 6;

        char *pos = strstr(msg + JSON_OFFSET - adjust_offset, "]");
        if(*(pos - 1) == '[')
        {
            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", "8");
        }
        else
        {

            insertAfterSubstring(msg + JSON_OFFSET - adjust_offset, "]", ",8");
        }
    }
    if(check_if_end(p_game))
    {
        p_game->state = GAME_WIN;
        lv_label_set_text(ui_Label6, "GAME WON!!"); return;
    }
    telemetry_send("WES/Neptune/game", msg);
    printf("%s %d\n", msg, strlen(msg));

    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");
}

void exit_game(lv_event_t *e)
{
    // Your code here

    /* in the main screen on the top left there is a button that exits the game */
    _exit_game();
}

void _exit_game()
{
    game_delete(p_game);
    p_game = NULL;
    lv_label_set_text(ui_znak0, "");
    lv_label_set_text(ui_znak1, "");
    lv_label_set_text(ui_znak2, "");
    lv_label_set_text(ui_znak3, "");
    lv_label_set_text(ui_znak4, "");
    lv_label_set_text(ui_znak5, "");
    lv_label_set_text(ui_znak6, "");
    lv_label_set_text(ui_znak7, "");
    lv_label_set_text(ui_znak8, "");
    memset(msg, '\0', 100);
}

void challenge(lv_event_t *e)
{
    // Your code here
    if(!wifi_is_wifi_connected() || p_game != NULL)
        return;

    p_game = game_new();
    game_start(p_game);
    p_game->state = GAME_IN_PROGRESS;

    snprintf(msg,
             sizeof(msg),
             "{"
             "\"indexX\": [], "
             "\"indexO\": [], "
             "\"turn\": \"server\""
             "}");

    telemetry_send("WES/Neptune/game", msg);

    is_my_turn = false;
    lv_label_set_text(ui_Label6, "Wait for your turn...");

}
