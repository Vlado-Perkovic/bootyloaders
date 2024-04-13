/**
 * @file game_object.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "game_object.h"

//---------------------------------- MACROS -----------------------------------
#define MAP_WIDTH  (40U)
#define MAP_HEIGHT (40U)
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief default function for game object movement
 *
 * @param p_self pointer to a game object
 * @param delta_x new x value
 * @param delta_y new y value
 */
static void _game_object_default_move(game_object_t *p_self, int8_t delta_x, int8_t delta_y);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static game_object_ops_t default_ops = {
    ._move = _game_object_default_move,
};
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

void game_object_move(game_object_t *p_self, int8_t delta_x, int8_t delta_y)
{
    p_self->p_ops->_move(p_self, delta_x, delta_y);
}

void _game_object_init(game_object_t *p_self)
{
    p_self->p_ops = &default_ops;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------

static void _game_object_default_move(game_object_t *p_self, int8_t delta_x, int8_t delta_y)
{
    /* if the move is not out of bounds */
    if(((p_self->x + delta_x - ceil(p_self->width / 2)) > 0) && ((p_self->x + delta_x + (p_self->width / 2))) <= MAP_WIDTH)
    {
        p_self->x += delta_x;
    }

    /* if the move is not out of bounds */
    if(((p_self->y + delta_y - ceil(p_self->height / 2)) > 0) && ((p_self->y + delta_y + (p_self->height / 2))) <= MAP_HEIGHT)
    {
        p_self->y += delta_y;
    }
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
