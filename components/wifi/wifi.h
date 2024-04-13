/**
 * @file wifi.h
 *
 * @brief See the source file.
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

#ifndef __WIFI_H__
#define __WIFI_H__

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------- INCLUDES ----------------------------------
#include "wifi_driver.h"
//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------
typedef enum
{
    WIFI_OK = 0,

    // Warnings:
    WIFI_ALREADY_PROVISIONED = 10,

    // Errors:
    WIFI_ERROR_CONNECTION   = -10,
    WIFI_ERROR_PROVISIONING = -20,
    WIFI_ERROR              = -30,

    WIFI_COUNT
} wifi_err_t;

typedef enum
{
    WIFI_PROV_METHOD_UNKNOWN = -1,
    WIFI_PROV_METHOD_BLE     = 0,
    WIFI_PROV_METHOD_SOFTAP  = 1
} wifi_prov_method_t;

//---------------------- PUBLIC FUNCTION PROTOTYPES --------------------------
/**
 * @brief function that inits the wifi
 *
 * @return wifi_err_t wifi enum error values
 */
wifi_err_t wifi_init(void);

/**
 * @brief function that connect the wifi
 *
 * @return wifi_err_t wifi enum error values
 */
wifi_err_t wifi_connect(void);

/**
 * @brief function that diconnects the wifi
 *
 * @return wifi_err_t wifi enum error values
 */
wifi_err_t wifi_disconnect(void);

/**
 * @brief function that scans and prints out visible networks
 *
 * @return wifi_err_t wifi enum error values
 */
wifi_err_t wifi_scan(void);

/**
 * @brief function for provisioning
 *
 * @param method provisioning method
 * @return wifi_err_t wifi enum error values
 */
wifi_err_t wifi_provision(wifi_prov_method_t method);

/**
 * @brief function that checks if the wifi is provisioned
 *
 * @param pb_is_provisioned pointer to a boolean
 * @return wifi_err_t wifi enum error value
 */
wifi_err_t wifi_is_provisioned(bool *pb_is_provisioned);

/**
 * @brief function for checking is the wifi connected
 *
 * @return true if it is connected
 * @return false if its not connected
 */
bool wifi_is_wifi_connected();

/**
 * @brief function for turning off the wifi provision
 *
 */
void wifi_provision_stop(void);

/**
 * @brief function that registers a callback function on wifi status change
 *
 * @param cbk pointer to a callback function
 */
void wifi_register_on_status_changed(wifi_on_status_changed_cb_t cbk);
#ifdef __cplusplus
}
#endif

#endif // __WIFI_H__
