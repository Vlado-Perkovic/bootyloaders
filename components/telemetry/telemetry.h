/**
 * @file telemetry.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __TELEMETRY_H__
#define __TELEMETRY_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "telemetry_driver.h"
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

typedef enum
{
    TELEMETRY_OK = 0,
    // Errors:
    TELEMETRY_INIT_FAILED = -10,
    TELEMETRY_SEND_FAILED = -20,
    TELEMETRY_COUNT
} telemetry_err_t;
//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief init function for telemetry
 *
 * @return telemetry_err_t telemetry enum error
 */
telemetry_err_t telemetry_init(void);

/**
 * @brief function for sending messages via mqtt
 *
 * @param msg the message to be sent
 * @return telemetry_err_t telemetry enum error
 */

telemetry_err_t telemetry_connection_status_update(const char *p_msg);

/**
 * @brief function for registering callback functions
 *
 * @param p_cbk pointer to the callback function
 */
void telemetry_register_on_new_message(telemetry_on_new_message_cb_t p_cbk);
#ifdef __cplusplus
}
#endif

#endif // __TELEMETRY_H__
