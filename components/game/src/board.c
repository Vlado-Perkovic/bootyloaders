/**
 * @file board.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "board.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------

void board_move(board_t *p_self, bool is_player, int8_t pos)
{
    p_self->pos[pos] = is_player;
}

void board_init(board_t *p_self)
{
    for (int i = 0; i < 9; i++) {
        p_self->pos[i] = -1;
    }
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
