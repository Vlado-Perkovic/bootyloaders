/**
 * @file telemetry_driver.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __TELEMETRY_DRIVER_H__
#define __TELEMETRY_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "esp_event.h"
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief type for callback function to be called on new messages
 *
 */
typedef void (*telemetry_on_new_message_cb_t)(const char *);

/**
 * @brief init function for telemetry driver
 *
 * @return esp_err_t esp enum error
 */
esp_err_t telemetry_driver_init(void);

/**
 * @brief function for sending messages via mqtt
 *
 * @param msg the message to be sent
 * @return esp_err_t esp enum error
 */
esp_err_t telemetry_driver_connection_status_update(const char *msg);

esp_err_t telemetry_driver_send(const char* topic, const char *p_msg);

/**
 * @brief function for registering callback functions
 *
 * @param p_cbk pointer to the callback function
 */
void telemetry_driver_register_on_new_message(telemetry_on_new_message_cb_t p_cbk);
#ifdef __cplusplus
}
#endif

#endif // __TELEMETRY_DRIVER_H__
