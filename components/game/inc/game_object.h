/**
 * @file game_object.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdint.h>
#include <stdlib.h>
#include "math.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief a struct used for game objects
 *
 */
struct _game_object_t;

/**
 * @brief type for game objects used for abstraction
 *
 */
typedef struct _game_object_t game_object_t;

/**
 * @brief ops object that is basically a vtable
 *
 */
typedef struct
{
    void (*_move)(game_object_t *p_self, int8_t delta_x, int8_t delta_y);
} game_object_ops_t;

struct _game_object_t
{
    game_object_ops_t *p_ops;
    uint8_t            x;
    uint8_t            y;
    uint8_t            width;
    uint8_t            height;
    uint8_t            speed;
};

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief function that moves the game object
 *
 * @param p_obj pointer to an object
 * @param delta_x the difference from the new x coord from the old one
 * @param delta_y the difference from the new y coord from the old one
 */
void game_object_move(game_object_t *p_self, int8_t delta_x, int8_t delta_y);

/**
 * @brief init function for game object
 *
 * @param p_self
 */
void _game_object_init(game_object_t *p_self);

#ifdef __cplusplus
}
#endif

#endif // __GAME_OBJECT_H__
