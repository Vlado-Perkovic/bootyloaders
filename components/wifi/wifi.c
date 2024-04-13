/**
 * @file wifi.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "wifi.h"
#include "wifi_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

//---------------------------------- MACROS -----------------------------------

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static const char *TAG = "wifi station";

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
wifi_err_t wifi_init(void)
{
    wifi_err_t err = WIFI_OK;
    if(ESP_OK != wifi_driver_init())
    {
        ESP_LOGI(TAG, "WiFi initialization in STATION mode FAILED.");
        err = WIFI_ERROR_CONNECTION;
    }
    return err;
}

wifi_err_t wifi_connect(void)
{
    wifi_err_t err = WIFI_OK;
    if(ESP_OK != wifi_driver_connect())
    {
        ESP_LOGE(TAG, "WiFi connection FAILED.");
        err = WIFI_ERROR_CONNECTION;
    }
    return err;
}

wifi_err_t wifi_disconnect(void)
{
    wifi_err_t err = WIFI_OK;
    if(ESP_OK != wifi_driver_disconnect())
    {
        ESP_LOGE(TAG, "WiFi disconnect FAILED.");
        err = WIFI_ERROR_CONNECTION;
    }
    return err;
}

wifi_err_t wifi_scan(void)
{
    wifi_err_t err = WIFI_OK;
    if(ESP_OK != wifi_driver_scan())
    {
        ESP_LOGE(TAG, "WiFi scan FAILED.");
        err = WIFI_ERROR_CONNECTION;
    }
    return err;
}

wifi_err_t wifi_is_provisioned(bool *pb_is_provisioned)
{
    wifi_err_t err = WIFI_OK;

    if(NULL == pb_is_provisioned)
    {
        err = WIFI_ERROR;
    }

    if((WIFI_OK == err) && (ESP_OK != wifi_driver_is_prov_mgr_provisioned(pb_is_provisioned)))
    {
        err = WIFI_ERROR;
    }
    return err;
}

wifi_err_t wifi_provision(wifi_prov_method_t method)
{
    wifi_err_t err = WIFI_OK;

    if(WIFI_PROV_METHOD_BLE == method)
    {
        if(ESP_OK != wifi_driver_provision_ble())
        {
            err = WIFI_ERROR_PROVISIONING;
        }
    }

    else if(WIFI_PROV_METHOD_SOFTAP == method)
    {
    }

    else
    {
        ESP_LOGE(TAG, "Unknown provisioning method.");
        err = WIFI_ERROR_PROVISIONING;
    }
    return err;
}

bool wifi_is_wifi_connected()
{
    return wifi_driver_is_wifi_connected();
}

void wifi_provision_stop(void)
{
    wifi_driver_provision_stop();
}

void wifi_register_on_status_changed(wifi_on_status_changed_cb_t cbk)
{
    wifi_driver_register_on_status_changed(cbk);
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------

//---------------------------- INTERRUPT HANDLERS -----------------------------
