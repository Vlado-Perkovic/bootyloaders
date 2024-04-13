/**
 * @file ui_app.c
 *
 * @brief This file runs an UI application depending on a Kconfig parameter
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "ui_app.h"
// #include "bl_gui/bl_gui.h"
// #include "lvgl_demo/lvgl_demo.h"
#include "squareline/ui.h"
#include "game_engine.h"

#include <stdio.h>
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
void ui_app_init(void)
{

    // #ifdef CONFIG_UI_APP_BL_GUI
    //     bl_gui_init();
    //     printf("APP: BL gui\n");

    // #elif CONFIG_UI_APP_LVGL_DEMO
    //     lvgl_demo_init();
    //     printf("APP: LVGL demo\n");

    // #elif CONFIG_UI_APP_SQUARELINE
    ui_init();
    printf("APP: Squareline\n");

    // printf("VIMOSEEEEEEE\n");

    // #endif
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
