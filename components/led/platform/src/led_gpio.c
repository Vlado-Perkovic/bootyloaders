/**
* @file led_gpio.c

* @brief

* @par
*
* COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
* All rights reserved.
*/

//--------------------------------- INCLUDES ----------------------------------
#include <stdio.h>
#include "led_gpio.h"
#include <stdbool.h>
#include "driver/gpio.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
struct _led_gpio_t
{
    uint8_t pin;
    bool    b_is_active_on_high_level;
    bool    b_is_on;
};
//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief It configures the GPIO pin as an input, sets the interrupt type.
 *
 * @param [in] p_led a pointer to the led_gpio_t structure.
 *
 * @return Status of initialization.
 */
static esp_err_t _led_init(led_gpio_t *p_led);
/**
 * @brief Allocate memory for a led_gpio_t structure and return a pointer to it
 *
 * @return A pointer to a led_gpio_t struct.
 */
static led_gpio_t *_led_alloc(void);
/**
 * @brief This function frees the memory allocated for the led_gpio_t structure.
 *
 * @param [in] p_led A pointer to the led_gpio_t structure
 * function.
 */
static void _led_free(led_gpio_t *p_led);
//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

led_gpio_t *led_gpio_create(uint8_t pin, bool b_is_active_on_high_level)
{
    led_gpio_t *p_led = _led_alloc();

    if(NULL == p_led)
    {
        return NULL;
    }

    p_led->pin                       = pin;
    p_led->b_is_active_on_high_level = b_is_active_on_high_level;
    p_led->b_is_on                   = false;

    if(ESP_OK != _led_init(p_led))
    {
        _led_free(p_led);
        return NULL;
    }

    return p_led;
}

void led_gpio_destroy(led_gpio_t *p_led)
{
    if(NULL != p_led)
    {
        _led_free(p_led);
    }
}

void led_gpio_on(led_gpio_t *p_led)
{

    if((NULL == p_led) || (true == p_led->b_is_on))
    {
        return;
    }

    gpio_set_level(p_led->pin, (p_led->b_is_active_on_high_level) ? 1 : 0);
    p_led->b_is_on = true;
}

void led_gpio_off(led_gpio_t *p_led)
{
    if((NULL == p_led) || (false == p_led->b_is_on))
    {
        return;
    }

    gpio_set_level(p_led->pin, (p_led->b_is_active_on_high_level) ? 0 : 1);
    p_led->b_is_on = false;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
static esp_err_t _led_init(led_gpio_t *p_led)
{
    // Configure GPIO.
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << p_led->pin),
        .mode         = GPIO_MODE_OUTPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };

    esp_err_t esp_err = gpio_config(&io_conf);

    return esp_err;
}

static led_gpio_t *_led_alloc(void)
{
    return (led_gpio_t *)malloc(sizeof(led_gpio_t));
}

static void _led_free(led_gpio_t *p_led)
{
    free(p_led);
}
//---------------------------- INTERRUPT HANDLERS -----------------------------