/**
 * @file ui_app.c
 *
 * @brief This file runs an UI application depending on a Kconfig parameter
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "ui_app.h"
// #include "bl_gui/bl_gui.h"
// #include "lvgl_demo/lvgl_demo.h"
#include "squareline/ui.h"
#include "game_engine.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


#include <stdio.h>
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

/* -- use following constants to define the example mode ----------- */

// #define SPI_USED     // SPI interface is used, otherwise I2C
// #define FIFO_MODE    // multiple sample read mode
// #define INT_DATA     // data interrupts used (data ready and FIFO status)
// #define INT_EVENT    // inertial event interrupts used (wake-up, free fall or 6D/4D orientation)
// #define INT_CLICK    // click detection interrupts used

/* -- includes ----------------------------------------------------- */

#include "lis3dh.h"

/** -- platform dependent definitions ------------------------------ */

#ifdef ESP_PLATFORM  // ESP32 (ESP-IDF)

// user task stack depth for ESP32
#define TASK_STACK_DEPTH 2048

// SPI interface definitions for ESP32
#define SPI_BUS       HSPI_HOST
#define SPI_SCK_GPIO  16
#define SPI_MOSI_GPIO 17
#define SPI_MISO_GPIO 18
#define SPI_CS_GPIO   19

#else  // ESP8266 (esp-open-rtos)

// user task stack depth for ESP8266
#define TASK_STACK_DEPTH 256

// SPI interface definitions for ESP8266
#define SPI_BUS       1
#define SPI_SCK_GPIO  14
#define SPI_MOSI_GPIO 13
#define SPI_MISO_GPIO 12
#define SPI_CS_GPIO   2   // GPIO 15, the default CS of SPI bus 1, can't be used

#endif  // ESP_PLATFORM

// I2C interface defintions for ESP32 and ESP8266
#define I2C_BUS       0
#define I2C_SCL_PIN   14
#define I2C_SDA_PIN   13
#define I2C_FREQ      I2C_FREQ_100K

// interrupt GPIOs defintions for ESP8266 and ESP32
#define INT1_PIN      5
#define INT2_PIN      4

/* -- user tasks --------------------------------------------------- */

static lis3dh_sensor_t* sensor;

/**
 * Common function used to get sensor data.
 */
void read_data ()
{


    lis3dh_float_data_t  data;

    if (lis3dh_new_data (sensor) &&
        lis3dh_get_float_data (sensor, &data))
        // max. full scale is +-16 g and best resolution is 1 mg, i.e. 5 digits
        printf("%.3f LIS3DH (xyz)[g] ax=%+7.3f ay=%+7.3f az=%+7.3f\n",
               (double)sdk_system_get_time()*1e-3, 
                data.ax, data.ay, data.az);
        
}


/*
 * In this example, user task fetches the sensor values every seconds.
 */

void user_task_periodic(void *pvParameters)
{
    vTaskDelay (100/portTICK_PERIOD_MS);
    
    while (1)
    {
        // read sensor data
        read_data ();
        
        // passive waiting until 1 second is over
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}


/* -- main program ------------------------------------------------- */

void init()
{
    // Set UART Parameter.
    uart_set_baud(0, 115200);
    // Give the UART some time to settle
    vTaskDelay(1);

    /** -- MANDATORY PART -- */


    // init all I2C bus interfaces at which LIS3DH  sensors are connected
    i2c_init (I2C_BUS, I2C_SCL_PIN, I2C_SDA_PIN, I2C_FREQ);
    
    // init the sensor with slave address LIS3DH_I2C_ADDRESS_1 connected to I2C_BUS.
    sensor = lis3dh_init_sensor (I2C_BUS, LIS3DH_I2C_ADDRESS_1, 0);

    
    if (sensor)
    {

        
        /** -- SENSOR CONFIGURATION PART --- */

        // set polarity of INT signals if necessary
        // lis3dh_config_int_signals (sensor, lis3dh_high_active);

       

        // configure HPF and reset the reference by dummy read
        lis3dh_config_hpf (sensor, lis3dh_hpf_normal, 0, true, true, true, true);
        lis3dh_get_hpf_ref (sensor);
        
        // enable ADC inputs and temperature sensor for ADC input 3
        lis3dh_enable_adc (sensor, true, true);
        
        // LAST STEP: Finally set scale and mode to start measurements
        lis3dh_set_scale(sensor, lis3dh_scale_2_g);
        lis3dh_set_mode (sensor, lis3dh_odr_10, lis3dh_high_res, true, true, true);

        /** -- TASK CREATION PART --- */

        // must be done last to avoid concurrency situations with the sensor
        // configuration part

       

        // create a user task that fetches data from sensor periodically
        xTaskCreate(user_task_periodic, "user_task_periodic", TASK_STACK_DEPTH, NULL, 2, NULL);

    }
    else
        printf("Could not initialize LIS3DH sensor\n");
}
//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void ui_app_init(void)
{

    // #ifdef CONFIG_UI_APP_BL_GUI
    //     bl_gui_init();
    //     printf("APP: BL gui\n");

    // #elif CONFIG_UI_APP_LVGL_DEMO
    //     lvgl_demo_init();
    //     printf("APP: LVGL demo\n");

    // #elif CONFIG_UI_APP_SQUARELINE
    ui_init();
    //init();
    printf("APP: Squareline\n");

    // printf("VIMOSEEEEEEE\n");

    // #endif
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
