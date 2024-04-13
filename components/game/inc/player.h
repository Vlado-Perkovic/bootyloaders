/**
 * @file player.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "game_object.h"
#include <stdbool.h>
//---------------------------------- MACROS -----------------------------------
#define PLAYER_SPEED (2U)
//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief struct for player object derived from game object
 *
 */
struct _game_player_t;

/**
 * @brief type used for abstraction of game player object
 *
 */
typedef struct _game_player_t game_player_t;

struct _game_player_t
{
    game_object_t base;
    uint8_t       no_of_torpedos;
    uint8_t       no_of_nets;
};
//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief private constructor for hero object
 *
 * @param p_self pointer to a screen object
 * @return true if successful
 * @return false otherwise
 */
bool game_player_init(game_player_t *p_self, uint8_t init_x, uint8_t init_y);

#ifdef __cplusplus
}
#endif

#endif // __PLAYER_H__
