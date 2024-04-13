/**
 * @file kraken.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __KRAKEN_H__
#define __KRAKEN_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "game_object.h"
#include <stdbool.h>
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief struct for kraken object derived from game object
 *
 */
struct _game_kraken_t;

/**
 * @brief type used for abstraction of game kraken object
 *
 */
typedef struct _game_kraken_t game_kraken_t;

struct _game_kraken_t
{
    game_object_t base;
};
//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief constructor for kraken object
 *
 * @param p_self pointer to a kraken object
 * @return true if successful
 * @return false otherwise
 */
bool game_kraken_init(game_kraken_t *p_self, uint8_t init_x, uint8_t init_y);

#ifdef __cplusplus
}
#endif

#endif // __KRAKEN_H__
