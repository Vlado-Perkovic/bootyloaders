/**
 * @file game_engine.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "player.h"
#include "kraken.h"
#include "map.h"

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <freertos/semphr.h>

//---------------------------------- MACROS -----------------------------------
#define DISTANCE(x1, y1, x2, y2) sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)))
#define DISTANCE_P_2_K(map)                                               \
    (sqrt(((map.player_x - map.kraken_x) * (map.player_x - map.kraken_x)) \
          + ((map.player_y - map.kraken_y) * (map.player_y - map.kraken_y))))

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief struct used for game object
 *
 */
struct _game_engine_t;
/**
 * @brief type for game object used for abstraction
 *
 */
typedef struct _game_engine_t game_engine_t;

/**
 * @brief enum for game states
 *
 */
typedef enum
{
    GAME_IN_PROGRESS,
    GAME_WIN,
    GAME_LOST,
} game_state_t;

/**
 * @brief struct for game engine
 *
 */
struct _game_engine_t
{
    game_player_t player;
    game_kraken_t kraken;
    game_map_t    map;
    game_state_t  state;
};

/**
 * @brief struct for game user input event
 *
 */
typedef struct
{
    uint8_t event_type;
    int8_t  delta_x;
    int8_t  delta_y;
} game_user_input_event_t;

/**
 * @brief enum for game events
 *
 */
typedef enum
{
    PLAYER_MOVE_EVENT,
    KRAKEN_MOVE_EVENT,
    TORPEDO_FIRING_EVENT,
    NET_FIRING_EVENT
} game_event_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief constructor for game engine object
 *
 * initializes all the struct members and creates a game loop timer
 * @return game_engine_t* pointer to the new game engine object
 */
game_engine_t *game_engine_new();

/**
 * @brief function that starts the game
 *
 * @param p_self pointer to a game engine object
 */
void game_engine_start(game_engine_t *p_self);

/**
 * @brief function destructor for game engine object
 *
 * @param p_self pointer to a game engine object
 */
void game_engine_delete(game_engine_t *p_self);

#ifdef __cplusplus
}
#endif

#endif // __GAME_ENGINE_H__
