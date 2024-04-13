/**
* @file joystick.h

* @brief See the source file.

* @par
*
* COPYRIGHT NOTICE: (c) 2022 Byte Lab Grupa d.o.o.
* All rights reserved.
*/

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdio.h>
#include <stdint.h>
//---------------------------------- MACROS -----------------------------------
#define JOYSTICK_MAX_POSITION (1000U)
#define CENTER_X              (500U)
#define CENTER_Y              (500U)
#define MIDDLE_AREA_RADIUS    (500)
//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief enum for joystick id
 *
 */
typedef enum
{
    JOYSTICK_1, /* The only one on the BL Dev Kit*/

    JOYSTICK_COUNT
} joystick_id_t;

/**
 * @brief enum for joystick errors
 *
 */
typedef enum
{
    JOYSTICK_ERR_NONE = 0,

    JOYSTICK_ERR                  = -1,
    JOYSTICK_ERR_INIT             = -2,
    JOYSTICK_ERR_UNKNOWN_INSTANCE = -3,
} joystick_err_t;

/**
 * @brief struct for the joystick position
 *
 */
typedef struct
{
    uint32_t position_x;
    uint32_t position_y;

} joystick_position_t;

/**
 * @brief struct for relative moves
 *
 * (0,1), (-1, -1) for example
 *
 */
typedef struct
{
    int8_t delta_x;
    int8_t delta_y;
} joystick_relative_move_t;

/**
 * @brief directions of joystick
 *
 */
typedef enum
{
    JOYSTICK_RIGHT,
    JOYSTICK_UP_RIGHT,
    JOYSTICK_UP,
    JOYSTICK_UP_LEFT,
    JOYSTICK_LEFT,
    JOYSTICK_DOWN_LEFT,
    JOYSTICK_DOWN,
    JOYSTICK_DOWN_RIGHT,
    JOYSTICK_MIDDLE

} joystick_direction_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief The function creates the joystick object.
 *
 * @param [in] joystick_id The id of the joystick to initialize.
 *
 * @return The status of initialization.
 */
joystick_err_t joystick_init(joystick_id_t joystick_id);

/**
 * @brief This function returns the joysticks position as a structure containing 2 positions
 * (for x and y axis). Both of the positions can be in the interval [0, JOYSTICK_MAX_POSITION].
 *
 * @param [in] joystick_id The id of the joystick which is being checked.
 * @param [out] p_ptntnmtr_position - pointer to joysticks position structure (for x and y axis positions).
 *
 * @return joystick_err_t error enum of joystick
 */
joystick_err_t joystick_position_get(joystick_id_t joystick_id, joystick_position_t *p_ptntnmtr_position);

/**
 * @brief Function that returns the joystick direction.
 *
 * provides validation through return enum error value. The direction is returned through the argument p_ptntnmtr_direction
 * @param joystick_id The id of the joystick which is being checked.
 * @param [out] p_ptntnmtr_direction - pointer to joysticks direction enum value
 * @return joystick_err_t error enum of joystick
 */
joystick_err_t joystick_direction_get(joystick_id_t joystick_id, joystick_direction_t *p_ptntnmtr_direction);

/**
 * @brief function that returns through the p_move parameter the relative move based on the direction
 *
 * @param joystick_id joystick id
 * @param p_move pointer to a move
 * @return joystick_err_t enum error value
 */
joystick_err_t joystick_relative_move_get(joystick_id_t joystick_id, joystick_relative_move_t *p_move);

#ifdef __cplusplus
}
#endif

#endif // __JOYSTICK_H__