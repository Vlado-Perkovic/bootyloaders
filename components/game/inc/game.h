/**
 * @file game.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __GAME_H__
#define __GAME_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <freertos/semphr.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief struct used for game object
 *
 */
struct _game_t;
/**
 * @brief type for game object used for abstraction
 *
 */
typedef struct _game_t game_t;

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
struct _game_t
{
   board_t board;
};

typedef enum
{
    X_EVENT,
    O_EVENT,
} game_event_t;

typedef struct
{
    game_event_t evt;
    uint8_t pos;
} game_move_event_t;


//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief constructor for game engine object
 *
 * initializes all the struct members and creates a game loop timer
 * @return game_t* pointer to the new game engine object
 */
game_t *game_new();

/**
 * @brief function that starts the game
 *
 * @param p_self pointer to a game engine object
 */
void game_start(game_t *p_self);

void check_if_end(game_t *p_self);

/**
 * @brief function destructor for game engine object
 *
 * @param p_self pointer to a game engine object
 */
void game_delete(game_t *p_self);

#ifdef __cplusplus
}
#endif

#endif // __GAME_H__
