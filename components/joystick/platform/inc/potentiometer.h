/**
* @file potentiometer.h

* @brief See the source file.

* @par
*
* COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
* All rights reserved.
*/

#ifndef __POTENTIOMETER_H__
#define __POTENTIOMETER_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <esp_event.h>

//---------------------------------- MACROS -----------------------------------
#define POTENTIOMETER_MAX_POSITION (1000U)

//-------------------------------- DATA TYPES ---------------------------------
// Struct is hidden on purpose from an user.
struct _potentiometer_t;
typedef struct _potentiometer_t potentiometer_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief It creates a potentiometer object and initializes it.
 *
 * @param [in] pin The GPIO pin number that the potentiometer is connected to.
 * @param [in] max_voltage_mv Maximal voltage (in mV) that the ADC can receive from the potentiometers output.
 * @param [in] b_is_reversed True if the potentiometers logic is reversed. False otherwise.
 * The logic is reversed if the potentiometer is in a starting position for maximal voltage.
 * The logic is not reversed if the potentiometers starting position gives 0 V to the ADC.
 *
 * @return A pointer to a potentiometer_t struct.
 */
potentiometer_t *potentiometer_create(uint8_t pin, uint16_t max_voltage_mv, bool b_is_reversed);

/**
 * @brief This function frees the memory allocated for the potentiometer_t structure.
 *
 * @param [in] p_potentiometer A pointer to the potentiometer_t structure.
 */
void potentiometer_destroy(potentiometer_t *p_potentiometer);

/**
 * @brief This function returns the position of the potentiometer in the interval: [0, POTENTIOMETER_MAX_POSITION]
 * through param [out] p_ptntnmtr_position.
 *
 * 0 means that the potentiometer is in a starting position. POTENTIOMETER_MAX_POSITION is returned
 * if the potentiometer is turned all the way.
 *
 * @param [in] p_potentiometer A pointer to the potentiometer_t structure.
 * @param [out] p_ptntnmtr_position stores a position of the potentiometer
 *
 * @return Potentiometers position in the interval: [0, POTENTIOMETER_MAX_POSITION].
 */
esp_err_t potentiometer_position_get(potentiometer_t *p_potentiometer, uint32_t *p_ptntnmtr_position);

#ifdef __cplusplus
}
#endif

#endif // __POTENTIOMETER_H__