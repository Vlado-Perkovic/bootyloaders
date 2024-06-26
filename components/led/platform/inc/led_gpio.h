/**
* @file led_gpio.h

* @brief See the source file.

* @par
*
* COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
* All rights reserved.
*/

#ifndef __LED_GPIO_H__
#define __LED_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdint.h>
#include <stdbool.h>
//---------------------------------- MACROS -----------------------------------
struct _led_gpio_t;
typedef struct _led_gpio_t led_gpio_t;
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief It creates a LED GPIO object and initializes it.
 *
 * @param [in] pin The GPIO pin number that the button is connected to.
 *
 * @return A pointer to a led_gpio_t struct.
 */
led_gpio_t *led_gpio_create(uint8_t pin, bool b_is_active_on_high_level);

/**
 * @brief This function frees the memory allocated for the led_gpio_t structure.
 *
 * @param [in] p_led A pointer to the led_gpio_t structure that was created by the led_gpio_create()
 * function.
 */
void led_gpio_destroy(led_gpio_t *p_led);

/**
 * @brief Turns LED GPIO on.
 *
 * @param [in] p_led A pointer to the led_gpio_t structure that was created by the led_gpio_create()
 * function.
 */
void led_gpio_on(led_gpio_t *p_led);

/**
 * @brief Turns LED GPIO off.
 *
 * @param [in] p_led A pointer to the led_gpio_t structure that was created by the led_gpio_create()
 * function.
 */
void led_gpio_off(led_gpio_t *p_led);

#ifdef __cplusplus
}
#endif

#endif // __LED_GPIO_H__