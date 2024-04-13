/**
* @file led.c

* @brief

* @par
*
* COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
* All rights reserved.
*/

//--------------------------------- INCLUDES ----------------------------------
#include "led.h"
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

//---------------------------------- MACROS -----------------------------------
#define FASTBLINK_MS (200U)
#define SLOWBLINK_MS (800U)

#define LED_TIMER_RESET(timer_hndl)  \
    do                               \
    {                                \
        xTimerStop(timer_hndl, 0);   \
        xTimerDelete(timer_hndl, 0); \
        timer_hndl = NULL;           \
    } while(0)

//-------------------------------- DATA TYPES ---------------------------------
typedef struct
{
    uint8_t       pin;
    bool          b_is_active_on_high_level;
    bool          b_is_on;
    led_gpio_t   *p_led;
    led_pattern_t e_pattern;
    TimerHandle_t p_timer_hndl;
    TimerHandle_t p_blink_timer_hndl;

} _led_config_t;
//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief Creates and starts the main timer
 *
 * @param led argument which specifies which led is used
 * @param _timer_period_ms period in ms
 */
static void _led_pattern_timer_main_create(led_name_t led, uint32_t _timer_period_ms);
/**
 * @brief Creates and starts the blink timer
 *
 * @param led argument which specifies which led is used
 * @param led_pattern argument which specifies which pattern is used
 */
static void _led_pattern_timer_blink_create(led_name_t led, led_pattern_t led_pattern);

/**
 * @brief Main timer Callback function.
 *
 * @param time_handle - timer argument passed to the callback function.
 */
static void _led_pattern_timer_cb(TimerHandle_t time_handle);

/**
 * @brief Blink timer callback function
 *
 * @param time_handle - timer argument passed to the callback function.
 */
static void _led_blink_pattern_timer_cb(TimerHandle_t time_handle);

/**
 * @brief function that sets the behaviour of LED when LED_PATTERN_NONE is chosen
 *
 * @param led - argument which specifies which led is used
 */
static void _led_none_pattern_case(led_name_t led);

/**
 * @brief function that sets the behaviour of LED when LED_PATTERN_KEEP_ON is chosen
 *
 * @param led - argument which specifies which led is used
 * @param timeout_ms - period in ms
 */
static void _led_keep_on_pattern_case(led_name_t led, uint32_t timeout_ms);

/**
 * @brief generic function that deals with blinking patterns
 *
 * @param led - argument which specifies which led is used
 * @param led_pattern - argument which specifies which pattern is used
 * @param timeout_ms - period in ms
 */
static void _led_blink_pattern_case(led_name_t led, led_pattern_t led_pattern, uint32_t timeout_ms);

/**
 * @brief private helper function that resets the main timer
 *
 * @param led - an instance of an enum led name
 */
static void _led_reset_main_timer(led_name_t led);

/**
 * @brief private helper function that resets the blink timer
 *
 * @param led - an instance of an enum led name
 */
static void _led_reset_blink_timer(led_name_t led);
//------------------------- STATIC DATA & CONSTANTS ---------------------------
static _led_config_t _led_info[LED_COUNT] = {
    // GPIO LEDS
    { .pin                       = 26U,
      .b_is_active_on_high_level = true,
      .b_is_on                   = false,
      .p_led                     = NULL,
      .e_pattern                 = LED_PATTERN_NONE,
      .p_timer_hndl              = NULL,
      .p_blink_timer_hndl        = NULL },

    { .pin                       = 27U,
      .b_is_active_on_high_level = true,
      .b_is_on                   = false,
      .p_led                     = NULL,
      .e_pattern                 = LED_PATTERN_NONE,
      .p_timer_hndl              = NULL,
      .p_blink_timer_hndl        = NULL },

    { .pin                       = 14U,
      .b_is_active_on_high_level = true,
      .b_is_on                   = false,
      .p_led                     = NULL,
      .e_pattern                 = LED_PATTERN_NONE,
      .p_timer_hndl              = NULL,
      .p_blink_timer_hndl        = NULL },
};
//------------------------------- GLOBAL DATA ---------------------------------
//------------------------------ PUBLIC FUNCTIONS -----------------------------
led_err_t led_init(led_name_t led)
{
    /* VALIDATE LED */
    if(LED_COUNT <= led)
    {
        return LED_ERR_INVALID_LED;
    }

    _led_info[led].p_led = led_gpio_create(_led_info[led].pin, _led_info[led].b_is_active_on_high_level);

    if(NULL == _led_info[led].p_led)
    {
        return LED_ERR_INIT;
    }

    return LED_ERR_NONE;
}

led_err_t led_on(led_name_t led)
{
    led_err_t led_err = LED_ERR_NONE;

    if(led < LED_COUNT)
    {
        led_gpio_on(_led_info[led].p_led);
    }

    return led_err;
}

led_err_t led_off(led_name_t led)
{
    led_err_t led_err = LED_ERR_NONE;

    if(led < LED_COUNT)
    {
        led_gpio_off(_led_info[led].p_led);
    }

    return led_err;
}


led_err_t led_pattern_run(led_name_t led, led_pattern_t led_pattern, uint32_t timeout_ms)
{
    /* VALIDATE LED */
    if(LED_COUNT <= led)
    {
        return LED_ERR_INVALID_LED;
    }
    /* VALIDATE PATTERN */
    if(LED_PATTERN_COUNT <= led_pattern)
    {
        return LED_ERR_INVALID_PATTERN;
    }

    switch(led_pattern)
    {
        case LED_PATTERN_NONE:
            _led_none_pattern_case(led);
            break;
        case LED_PATTERN_KEEP_ON:
            _led_keep_on_pattern_case(led, timeout_ms);
            break;
        case LED_PATTERN_SLOWBLINK:
            /* FALL THROUGH */

        case LED_PATTERN_FASTBLINK:
            _led_blink_pattern_case(led, led_pattern, timeout_ms);
            break;

        default:
            break;
    }

    return LED_ERR_NONE;
}

led_err_t led_pattern_reset(led_name_t led)
{
    /* VALIDATE LED */
    if(LED_COUNT <= led)
    {
        return LED_ERR_INVALID_LED;
    }

    _led_none_pattern_case(led);

    return LED_ERR_NONE;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _led_none_pattern_case(led_name_t led)
{
    _led_info[led].e_pattern = LED_PATTERN_NONE;

    /* taking care of both kinds of timers in a complete reset */
    _led_reset_blink_timer(led);
    _led_reset_main_timer(led);

    led_gpio_off(_led_info[led].p_led);
}

static void _led_keep_on_pattern_case(led_name_t led, uint32_t timeout_ms)
{
    _led_info[led].e_pattern = LED_PATTERN_KEEP_ON;

    _led_reset_blink_timer(led);
    _led_reset_main_timer(led);

    led_gpio_on(_led_info[led].p_led);

    _led_pattern_timer_main_create(led, timeout_ms);
}

static void _led_blink_pattern_case(led_name_t led, led_pattern_t led_pattern, uint32_t timeout_ms)
{
    _led_info[led].e_pattern = led_pattern;

    _led_reset_main_timer(led);

    _led_pattern_timer_main_create(led, timeout_ms);
    _led_pattern_timer_blink_create(led, led_pattern);
}

static void _led_pattern_timer_main_create(led_name_t led, uint32_t _timer_period_ms)
{
    _led_reset_main_timer(led);

    /* CREATE TIMER */
    _led_info[led].p_timer_hndl
        = xTimerCreate("pattern_timer", (_timer_period_ms / portTICK_PERIOD_MS), pdFALSE, (void *)led, _led_pattern_timer_cb);

    if(NULL == _led_info[led].p_timer_hndl)
    {
        printf("Main timer creation failed!\n");
        return;
    }

    /* START TIMER */
    if(xTimerStart(_led_info[led].p_timer_hndl, 0) != pdPASS)
    {
        printf("The main timer could not be set into the Active state.\n");
        return;
    }
}

static void _led_pattern_timer_blink_create(led_name_t led, led_pattern_t led_pattern)
{
    _led_reset_blink_timer(led);

    /* CREATE TIMER */
    uint32_t period = ((LED_PATTERN_SLOWBLINK == led_pattern) ? SLOWBLINK_MS : FASTBLINK_MS);
    _led_info[led].p_blink_timer_hndl
        = xTimerCreate("blink_pattern_timer", (period / portTICK_PERIOD_MS), pdTRUE, (void *)led, _led_blink_pattern_timer_cb);

    if(NULL == _led_info[led].p_blink_timer_hndl)
    {
        printf("Blink timer creation failed!\n");
        return;
    }

    /* START TIMER */
    if(xTimerStart(_led_info[led].p_blink_timer_hndl, 0) != pdPASS)
    {
        printf("The blink timer could not be set into the Active state.\n");
        return;
    }
}
static void _led_reset_main_timer(led_name_t led)
{
    if(NULL != _led_info[led].p_timer_hndl)
    {
        LED_TIMER_RESET(_led_info[led].p_timer_hndl);
    }
}

static void _led_reset_blink_timer(led_name_t led)
{
    if(NULL != _led_info[led].p_blink_timer_hndl)
    {
        LED_TIMER_RESET(_led_info[led].p_blink_timer_hndl);
    }
}

static void _led_pattern_timer_cb(TimerHandle_t time_handle)
{
    led_name_t led = (led_name_t)pvTimerGetTimerID(time_handle);

    led_pattern_reset(led);
}

static void _led_blink_pattern_timer_cb(TimerHandle_t time_handle)
{
    led_name_t led = (led_name_t)pvTimerGetTimerID(time_handle);
    if(_led_info[led].b_is_on)
    {
        led_gpio_off(_led_info[led].p_led);
        _led_info[led].b_is_on = false;
    }
    else
    {
        led_gpio_on(_led_info[led].p_led);
        _led_info[led].b_is_on = true;
    }
}
//---------------------------- INTERRUPT HANDLERS -----------------------------