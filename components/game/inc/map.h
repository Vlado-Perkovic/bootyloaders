/**
 * @file map.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __MAP_H__
#define __MAP_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdint.h>
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief struct for map objects
 *
 */
struct _game_map_t;

/**
 * @brief type used for abstraction
 *
 */
typedef struct _game_map_t game_map_t;

struct _game_map_t
{
    uint8_t player_x;
    uint8_t player_y;
    uint8_t kraken_x;
    uint8_t kraken_y;
};
//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief function for setting the values of a map
 *
 * @param p_self pointer to a map object
 * @param player_x player x coord
 * @param player_y player y coord
 * @param kraken_x kraken x coord
 * @param kraken_y kraken y coord
 */
void game_map_update(game_map_t *p_self, uint8_t player_x, uint8_t player_y, uint8_t kraken_x, uint8_t kraken_y);
#ifdef __cplusplus
}
#endif

#endif // __MAP_H__
