/**
 * @file player.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "player.h"

//---------------------------------- MACROS -----------------------------------
#define PLAYER_WIDTH       (7U)
#define PLAYER_HEIGHT      (7U)
#define NUMBER_OF_NETS     (6U)
#define NUMBER_OF_TORPEDOS (10U)
#define MAP_WIDTH          (40U)
#define MAP_HEIGHT         (40U)
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

/**
 * @brief private static destructor for player object
 *
 * @param p_self pointer to a player object
 */
static void _game_player_destroy(game_player_t *p_self);
//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
bool game_player_init(game_player_t *p_self, uint8_t init_x, uint8_t init_y)
{
    _game_object_init(&p_self->base);
    p_self->base.x         = init_x;
    p_self->base.y         = init_y;
    p_self->base.width     = PLAYER_WIDTH;
    p_self->base.height    = PLAYER_HEIGHT;
    p_self->base.speed     = PLAYER_SPEED;
    p_self->no_of_nets     = NUMBER_OF_NETS;
    p_self->no_of_torpedos = NUMBER_OF_TORPEDOS;
    return (p_self->base.p_ops) ? true : false;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------

static void _game_player_destroy(game_player_t *p_self)
{
    p_self->base.p_ops = NULL;
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
