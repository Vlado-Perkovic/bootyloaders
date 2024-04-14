/**
 * @file telemetry.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "telemetry.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
telemetry_err_t telemetry_init(void)
{
    telemetry_err_t err = TELEMETRY_OK;

    if(ESP_OK != telemetry_driver_init())
    {
        err = TELEMETRY_INIT_FAILED;
    }
    return err;
}

telemetry_err_t telemetry_connection_status_update(const char *p_msg)
{
    telemetry_err_t err = TELEMETRY_OK;

    if(ESP_OK != telemetry_driver_connection_status_update(p_msg))
    {
        err = TELEMETRY_SEND_FAILED;
    }
    return err;
}

telemetry_err_t telemetry_send(const char *topic, const char *p_msg)
{
    telemetry_err_t err = TELEMETRY_OK;

    if(ESP_OK != telemetry_driver_send(topic, p_msg))
    {
        err = TELEMETRY_SEND_FAILED;
    }
    return err;
}

void telemetry_register_on_new_message(telemetry_on_new_message_cb_t p_cbk)
{
    /* we allow NULL because it deregisters the callback */
    telemetry_driver_register_on_new_message(p_cbk);
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
