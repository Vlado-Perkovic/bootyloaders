/**
 * @file wifi_driver.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __WIFI_DRIVER_H__
#define __WIFI_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "esp_event.h"
#include <stdbool.h>

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
typedef enum
{
    WIFI_CONNECTION_STATUS_UNKNOWN      = -1,
    WIFI_CONNECTION_STATUS_CONNECTED    = 0,
    WIFI_CONNECTION_STATUS_DISCONNECTED = 1,
    WIFI_CONNECTION_STATUS_CONNECTING   = 2,
} wifi_connection_status_t;
//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief type for callbacks on wifi status change
 *
 */
typedef void (*wifi_on_status_changed_cb_t)(wifi_connection_status_t new_status);

/**
 * @brief function that inits wifi driver
 *
 * @return esp_err_t an enum err value
 */
esp_err_t wifi_driver_init(void);

/**
 * @brief funtion that connects to network
 *
 * @return esp_err_t an enum err value
 */
esp_err_t wifi_driver_connect(void);

/**
 * @brief function that disconnects the wifi driver from network
 *
 * @return esp_err_t an enum err value
 */
esp_err_t wifi_driver_disconnect(void);

/**
 * @brief function that scans and prints a number of visible networks
 *
 * @return esp_err_t an enum err value
 */
esp_err_t wifi_driver_scan(void);

/**
 * @brief function that provisions the wifi driver
 *
 * @param b_is_provisioned - boolean if the driver is already provisioned
 * @return esp_err_t an enum err value
 */
esp_err_t wifi_driver_provision_ble(void);

/**
 * @brief function for checking if wifi is provisioned
 *
 * @param pb_is_provisioned pointer to a boolean value
 * @return esp_err_t an enum err value
 */
esp_err_t wifi_driver_is_prov_mgr_provisioned(bool *pb_is_provisioned);

/**
 * @brief getter function for checking is the wifi connected
 *
 * @return true if it is connected
 * @return false if its not connected
 */
bool wifi_driver_is_wifi_connected();

/**
 * @brief function for turning off provision
 *
 */
void wifi_driver_provision_stop(void);

/**
 * @brief function that registers the callback on status change
 *
 * @param callback pointer to a callback function
 */
void wifi_driver_register_on_status_changed(wifi_on_status_changed_cb_t callback);

#ifdef __cplusplus
}
#endif

#endif // __WIFI_DRIVER_H__
