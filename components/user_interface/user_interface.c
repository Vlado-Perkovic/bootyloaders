/**
 * @file user_interface.c
 *
 * @brief This file is responsible for complete user interface (LEDs, buttons
 * and GUI).
 *
 * COPYRIGHT NOTICE: (c) 2024 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "user_interface.h"
#include "led.h"
#include "gui.h"
#include "gui_app.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "platform/inc/sht3x.h"
#include <stdio.h>
#include "esp_log.h"

//---------------------------------- MACROS -----------------------------------
#define USER_INTERFACE_QUEUE_SIZE (20U)
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------


#define UART_STACK_SIZE             (4096)

static const char *MAIN_TAG = "main";
static const char *SENSORS_TAG = "sensors";
/**
 * @brief User inteface task.
 *
 * @param [in] p_parameter This is the parameter that is passed to the task.
 */
static void _user_interface_task(void *p_parameter);

char scale = SCALE_CELCIUS;
float temperature = 0.0;
float humidity = 0.0;

void sensors_task(void *arg) {
    // init
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };

    ESP_ERROR_CHECK(i2c_param_config(I2C_MASTER_NUM, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_MASTER_NUM, i2c_config.mode,
                    I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));

    esp_log_level_set(SENSORS_TAG, ESP_LOG_INFO);

    #if defined(SENSORS_SCALE_F)
    scale = SCALE_FAHRENHEIT;
    #elif defined(SENSORS_SCALE_K)
    scale = SCALE_KELVIN;
    #endif
 // ---------
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    for(;;) {
        // start meas
        sht3x_start_periodic_measurement();

        sht3x_sensors_values_t sensors_values = {
            .temperature = 0x00,
            .humidity = 0x00
        };

        // ------
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        // read

        if(sht3x_read_measurement(&sensors_values) != ESP_OK) {
            ESP_LOGE(SENSORS_TAG, "Sensors read measurement error!");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        float temperature = sensors_values.temperature;
        float humidity = sensors_values.humidity;


        #if defined(SENSORS_SCALE_F)
        temperature = FAHRENHEIT(temperature);
        #elif defined(SENSORS_SCALE_K)
        temperature = KELVIN(temperature);
        #endif

        ESP_LOG_BUFFER_HEX_LEVEL(SENSORS_TAG, &sensors_values, sizeof(sensors_values), ESP_LOG_DEBUG);
// -------------

// stop
        sht3x_stop_periodic_measurement();

        ESP_LOGI(SENSORS_TAG, "Temperature %2.1f °%c - Humidity %2.1f%%", temperature, scale, humidity);
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static TaskHandle_t p_user_interface_task = NULL;

//------------------------------- GLOBAL DATA ---------------------------------
QueueHandle_t p_user_interface_queue = NULL;

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void user_interface_init(void)
{
    led_init(LED_BLUE);
    gui_init();

    p_user_interface_queue = xQueueCreate(USER_INTERFACE_QUEUE_SIZE, sizeof(gui_app_event_t));
    if(p_user_interface_queue == NULL)
    {
        printf("User interface queue was not initialized successfully\n");
        return;
    }

    if(pdPASS != xTaskCreate(&_user_interface_task, "user_interface_task", 2 * 1024, NULL, 5, &p_user_interface_task))
    {
        printf("User interface task was not initialized successfully\n");
        return;
    }

    xTaskCreate(sensors_task, "sensors_task", UART_STACK_SIZE, NULL, configMAX_PRIORITIES-9, NULL);
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _user_interface_task(void *p_parameter)
{
    gui_app_event_t gui_event;

    for(;;)
    {
        /* Blockingly wait on an event. */
        if((p_user_interface_queue != NULL) && (xQueueReceive(p_user_interface_queue, &gui_event, portMAX_DELAY) == pdTRUE))
        {
            printf("GUI event received %d\n", gui_event);

            switch(gui_event)
            {
                case GUI_APP_EVENT_BUTTON_LED_ON_PRESSED:
                    led_on(LED_BLUE);
                    break;

                case GUI_APP_EVENT_BUTTON_LED_OFF_PRESSED:
                    led_off(LED_BLUE);
                    break;
                default:
                    printf("Uknown GUI event\n");
                    break;
            }
        }


    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
