/**
 * @file joystick.c
 *
 * @brief This file implements Joysticks.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "joystick.h"
#include "stdbool.h"
#include "potentiometer.h"
#include "math.h"
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
typedef struct
{
    uint8_t          pin_x;
    uint8_t          pin_y;
    uint16_t         max_voltage_mv; /* Max voltage in mV*/
    bool             b_is_reversed_x;
    bool             b_is_reversed_y;
    potentiometer_t *p_ptntmtr_x;
    potentiometer_t *p_ptntmtr_y;

} _joystick_config_t;

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief private function for creating a joystick
 *
 * initializes two potentiometers for x and y axis and adds them to config
 * @param joystick_id - an instance of enum joystick
 * @return joystick_err_t - an instance of enum joystick error
 */
static joystick_err_t _joystick_create(joystick_id_t joystick_id);
/**
 * @brief private function that fetches the data from potentiometers
 *
 * @param joystick_id - an instance of enum joystick
 * @param [out] p_joystick_position - pointer to a position object
 * @return joystick_err_t - error
 */
static joystick_err_t _joystick_position_get(joystick_id_t joystick_id, joystick_position_t *p_joystick_position);

/**
 * @brief private function that fetches the direction of the joystick
 *
 * @param joystick_id - an instance of enum joystick
 * @param pos - position object of the joystick
 * @return joystick_direction_t - enum direction value
 */
static joystick_direction_t _joystick_direction_get(joystick_id_t joystick_id, joystick_position_t pos);

/**
 * @brief function that returns the relative move based on the direction of the joystick
 *
 * @param direction direction object instance
 * @param [out] p_move pointer to a relative move object
 */
static void _joystick_relative_move_get(joystick_direction_t direction, joystick_relative_move_t *p_move);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static _joystick_config_t _joystick_info[JOYSTICK_COUNT] = {
    { .pin_x           = 34,
      .pin_y           = 35,
      .max_voltage_mv  = 3300,
      .b_is_reversed_x = true,
      .b_is_reversed_y = true,
      .p_ptntmtr_x     = NULL,
      .p_ptntmtr_y     = NULL },
};
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
joystick_err_t joystick_init(joystick_id_t joystick_id)
{

    /* VALIDATE JOYSTICK ID */
    if(JOYSTICK_COUNT <= joystick_id)
    {
        return JOYSTICK_ERR_UNKNOWN_INSTANCE;
    }

    return _joystick_create(joystick_id);
}

joystick_err_t joystick_position_get(joystick_id_t joystick_id, joystick_position_t *p_ptntnmtr_position)
{

    /* VALIDATE JOYSTICK ID */
    if(JOYSTICK_COUNT <= joystick_id)
    {
        printf("Invalid joystick id.\n");
        return JOYSTICK_ERR_UNKNOWN_INSTANCE;
    }

    return _joystick_position_get(joystick_id, p_ptntnmtr_position);
}

joystick_err_t joystick_direction_get(joystick_id_t joystick_id, joystick_direction_t *p_ptntnmtr_direction)
{
    /* VALIDATE JOYSTICK ID */
    joystick_err_t err = JOYSTICK_ERR_NONE;
    if(JOYSTICK_COUNT <= joystick_id)
    {
        printf("Invalid joystick id.\n");
        err = JOYSTICK_ERR_UNKNOWN_INSTANCE;
    }

    joystick_position_t pos;
    if((JOYSTICK_ERR_NONE == err) && (JOYSTICK_ERR_NONE != _joystick_position_get(joystick_id, &pos)))
    {
        err = JOYSTICK_ERR;
    }

    if((JOYSTICK_ERR_NONE == err))
    {
        *p_ptntnmtr_direction = _joystick_direction_get(joystick_id, pos);
    }
    else
    {
        /* default it to middle since there is no error handling */
        *p_ptntnmtr_direction = JOYSTICK_MIDDLE;
    }
    return err;
}

joystick_err_t joystick_relative_move_get(joystick_id_t joystick_id, joystick_relative_move_t *p_move)
{
    joystick_err_t err = JOYSTICK_ERR_NONE;
    if(JOYSTICK_COUNT <= joystick_id)
    {
        printf("Invalid joystick id.\n");
        err = JOYSTICK_ERR_UNKNOWN_INSTANCE;
    }
    joystick_direction_t direction;
    joystick_direction_get(joystick_id, &direction);
    _joystick_relative_move_get(direction, p_move);
    return err;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
static joystick_err_t _joystick_create(joystick_id_t joystick_id)
{
    /* CREATE X AND Y AXIS */
    potentiometer_t *p_ptntmtr_x = potentiometer_create(
        _joystick_info[joystick_id].pin_x, _joystick_info[joystick_id].max_voltage_mv, _joystick_info[joystick_id].b_is_reversed_x);

    potentiometer_t *p_ptntmtr_y = potentiometer_create(
        _joystick_info[joystick_id].pin_y, _joystick_info[joystick_id].max_voltage_mv, _joystick_info[joystick_id].b_is_reversed_y);

    if((NULL == p_ptntmtr_x) || (NULL == p_ptntmtr_y))
    {
        return JOYSTICK_ERR_INIT;
    }

    _joystick_info[joystick_id].p_ptntmtr_x = p_ptntmtr_x;
    _joystick_info[joystick_id].p_ptntmtr_y = p_ptntmtr_y;

    return JOYSTICK_ERR_NONE;
}

static joystick_err_t _joystick_position_get(joystick_id_t joystick_id, joystick_position_t *p_joystick_position)
{
    joystick_position_t joystick_position;
    joystick_position.position_x = 0;
    joystick_position.position_y = 0;

    joystick_err_t err = JOYSTICK_ERR_NONE;

    if((NULL == _joystick_info[joystick_id].p_ptntmtr_x)
       || (ESP_OK != potentiometer_position_get(_joystick_info[joystick_id].p_ptntmtr_x, &joystick_position.position_x)))
    {
        err = JOYSTICK_ERR;
    }
    if((NULL == _joystick_info[joystick_id].p_ptntmtr_y)
       || (ESP_OK != potentiometer_position_get(_joystick_info[joystick_id].p_ptntmtr_y, &joystick_position.position_y)))
    {
        err = JOYSTICK_ERR;
    }

    p_joystick_position->position_x = joystick_position.position_x;
    p_joystick_position->position_y = joystick_position.position_y;

    return err;
}

static joystick_direction_t _joystick_direction_get(joystick_id_t joystick_id, joystick_position_t pos)
{
    /* the default state is MIDDLE */
    joystick_direction_t direction = JOYSTICK_MIDDLE;

    int x = pos.position_x - CENTER_X;
    int y = pos.position_y - CENTER_Y;

    /* calculate the angle in radians and convert to degrees
    note: we transfer the coordinates to the first quadrant */
    double angle = atan2(abs(y), abs(x)) * 180.0 / M_PI;

    /* since the angle is all calculated in the first quadrant, we have to adjust the angle for the other quadrants */
    if((pos.position_x >= CENTER_X) && (pos.position_y >= CENTER_Y))
    {
        /* this is fine since it is the first quadrant */
    }
    else if((pos.position_x < CENTER_X) && (pos.position_y >= CENTER_Y))
    {
        /* second quadrant */
        angle = 180.0 - angle;
    }
    else if((pos.position_x < CENTER_X) && (pos.position_y < CENTER_Y))
    {
        /* third quadrant */
        angle = angle + 180.0;
    }
    else if((pos.position_x >= CENTER_X) && (pos.position_y < CENTER_Y))
    {
        /* fourth quadrant */
        angle = 360.0 - angle;
    }

    double distance_from_center = sqrt((x * x) + (y * y));

    /* here the coordinate system is divided into 8 parts and each is 45 degrees -> 360/8 = 45
     *  we treat the circle with radius MIDDLE_AREA_RADIUS as the middle.
     */
    if(MIDDLE_AREA_RADIUS >= distance_from_center)
    {
        direction = JOYSTICK_MIDDLE;
    }
    else if(((angle >= 337.5) && (angle <= 360)) || ((angle >= 0) && (angle < 22.5)))
    {
        direction = JOYSTICK_RIGHT;
    }
    else if((angle >= 22.5) && (angle < 67.5))
    {
        direction = JOYSTICK_UP_RIGHT;
    }
    else if((angle >= 67.5) && (angle < 112.5))
    {
        direction = JOYSTICK_UP;
    }
    else if((angle >= 112.5) && (angle < 157.5))
    {
        direction = JOYSTICK_UP_LEFT;
    }
    else if((angle >= 157.5) && (angle < 202.5))
    {
        direction = JOYSTICK_LEFT;
    }
    else if((angle >= 202.5) && (angle < 247.5))
    {
        direction = JOYSTICK_DOWN_LEFT;
    }
    else if((angle >= 247.5) && (angle < 292.5))
    {
        direction = JOYSTICK_DOWN;
    }
    else if((angle >= 292.5) && (angle < 337.5))
    {
        direction = JOYSTICK_DOWN_RIGHT;
    }

    return direction;
}

static void _joystick_relative_move_get(joystick_direction_t direction, joystick_relative_move_t *p_move)
{
    switch(direction)
    {
        case JOYSTICK_RIGHT:
            p_move->delta_x = 1;
            p_move->delta_y = 0;
            break;

        case JOYSTICK_UP_RIGHT:
            p_move->delta_x = 1;
            p_move->delta_y = 1;

            break;

        case JOYSTICK_UP:
            p_move->delta_x = 0;
            p_move->delta_y = 1;

            break;

        case JOYSTICK_UP_LEFT:
            p_move->delta_x = -1;
            p_move->delta_y = 1;

            break;

        case JOYSTICK_LEFT:
            p_move->delta_x = -1;
            p_move->delta_y = 0;

            break;

        case JOYSTICK_DOWN_LEFT:
            p_move->delta_x = -1;
            p_move->delta_y = -1;

            break;

        case JOYSTICK_DOWN:
            p_move->delta_x = 0;
            p_move->delta_y = -1;

            break;

        case JOYSTICK_DOWN_RIGHT:
            p_move->delta_x = 1;
            p_move->delta_y = -1;

            break;
        default:
            p_move->delta_x = 0;
            p_move->delta_y = 0;
            break;
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------