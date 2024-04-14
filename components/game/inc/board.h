/**
 * @file board.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


//---------------------------------- MACROS -----------------------------------
#define BOARD_SIZE 9
//-------------------------------- DATA TYPES ---------------------------------
/**
 * @brief a struct used for game objects
 *
 */
struct _board_t;

/**
 * @brief type for game objects used for abstraction
 *
 */
typedef struct _board_t board_t;


struct _board_t
{
    int8_t            pos[9];
};

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------

/**
 * @brief init function for game object
 *
 * @param p_self
 */
void board_init(board_t *p_self);

#ifdef __cplusplus
}
#endif

#endif // __BOARD_H__
