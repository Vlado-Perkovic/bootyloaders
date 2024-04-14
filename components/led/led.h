/**
* @file led.h

* @brief See the source file.

* @par
*
* COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
* All rights reserved.
*/

#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdio.h>
#include <led_gpio.h>
#include <stdbool.h>
#include <stdint.h>
//---------------------------------- MACROS -----------------------------------
#define NO_TIMEOUT (UINT_MAX)

//-------------------------------- DATA TYPES ---------------------------------

typedef enum
{
    LED_PATTERN_NONE, /* LED is off */

    LED_PATTERN_KEEP_ON,   /* LED is on   */
    LED_PATTERN_SLOWBLINK, /* 1000 ms on, 1000 ms off */
    LED_PATTERN_FASTBLINK, /* 100 ms on, 100 ms off */

    LED_PATTERN_COUNT
} led_pattern_t;

typedef enum
{
    LED_RED,
    LED_GREEN,
    LED_BLUE,

    LED_COUNT
} led_name_t;

typedef enum
{
    LED_ERR_NONE = 0,

    LED_ERR_INIT            = -1,
    LED_ERR_INVALID_PATTERN = -2,
    LED_ERR_INVALID_LED     = -3,

} led_err_t;
//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief Init LED driver and configure all needed functionalities.
 *
 * @param [in] led - Name of the LED to be initialized.
 *
 * @return Status of initialization.
 */
led_err_t led_init(led_name_t led);
/**
 * @brief Init LED driver and configure all needed functionalities.
 *
 * @param [in] led - Name of the LED to be initialized.
 *
 * @return Status of initialization.
 */
led_err_t led_on(led_name_t led);

/**
 * @brief Init LED driver and configure all needed functionalities.
 *
 * @param [in] led - Name of the LED to be initialized.
 *
 * @return Status of initialization.
 */
led_err_t led_off(led_name_t led);

/**
 * @brief Set led pattern.
 *        Don't call this function from ISR.
 *
 * @param [in] led - LED name.
 * @param [in] led_pattern - LED pattern to be run.
 * @param [in] timeout_ms - timeout in milliseconds (if 0 run infinitely).
 *
 * @return Status of pattern starting.
 */
led_err_t led_pattern_run(led_name_t led, led_pattern_t led_pattern, uint32_t timeout_ms);

/**
 * @brief Reset LED pattern.
 *
 * @param [in] led - LED name.
 * .
 * @return Status of pattern reseting.
 */
led_err_t led_pattern_reset(led_name_t led);
/**
 * @brief The function turns LED on.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
led_err_t led_on(led_name_t led);

/**
 * @brief The function turns LED off.
 *
 * @param [in] led LED instance (e.g. LED_BLUE).
 *
 * @return esp_err_t ESP_OK on success, fail otherwise.
 */
led_err_t led_off(led_name_t led);

led_err_t led_custom_pattern(led_name_t led, uint32_t ON_state_ms);
#ifdef __cplusplus
}
#endif

#endif // __LED_H__
