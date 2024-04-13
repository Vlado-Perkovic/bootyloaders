/**
 * @file kraken.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "kraken.h"

//---------------------------------- MACROS -----------------------------------
#define KRAKEN_WIDTH  (7U)
#define KRAKEN_HEIGHT (7U)
#define KRAKEN_SPEED  (1U)
#define MAP_WIDTH     (40U)
#define MAP_HEIGHT    (40U)
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief function that moves kraken to a new location
 *
 * @param p_self pointer to a game object
 * @param x the new x coordinate
 * @param y the new y coordinate
 */
static void _game_kraken_move(game_object_t *p_self, int8_t x, int8_t y);

/**
 * @brief private static destructor for kraken object
 *
 * @param p_self pointer to a kraken object
 */
static void _game_kraken_destroy(game_kraken_t *p_self);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
/**
 * @brief a struct object that defines the ops of the kraken object
 *
 */
static const game_object_ops_t game_kraken_ops = {
    ._move = _game_kraken_move,
};
//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
bool game_kraken_init(game_kraken_t *p_self, uint8_t init_x, uint8_t init_y)
{
    _game_object_init(&p_self->base);
    p_self->base.p_ops  = &game_kraken_ops;
    p_self->base.x      = init_x;
    p_self->base.y      = init_y;
    p_self->base.width  = KRAKEN_WIDTH;
    p_self->base.height = KRAKEN_HEIGHT;
    p_self->base.speed  = KRAKEN_SPEED;
    return (p_self->base.p_ops) ? true : false;
}

//---------------------------- PRIVATE FUNCTIONS ------------------------------
static void _game_kraken_move(game_object_t *p_self, int8_t x, int8_t y)
{
    /* if the move is not out of bounds */
    if(((x - ceil(p_self->width / 2)) > 0) && ((x + (p_self->width / 2))) <= MAP_WIDTH)
    {
        p_self->x = x;
    }

    /* if the move is not out of bounds */
    if(((y - ceil(p_self->height / 2)) > 0) && ((y + (p_self->height / 2))) <= MAP_HEIGHT)
    {
        p_self->y = y;
    }
}

static void _game_kraken_destroy(game_kraken_t *p_self)
{
    p_self->base.p_ops = NULL;
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
