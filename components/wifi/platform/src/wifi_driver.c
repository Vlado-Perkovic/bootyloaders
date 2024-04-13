/**
 * @file wifi_driver.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "wifi_driver.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_mac.h"
#include <wifi_provisioning/manager.h>
#include <wifi_provisioning/scheme_ble.h>
#include "nvs_flash.h"

#include <string.h>

#include "lwip/err.h"
#include "lwip/sys.h"

//---------------------------------- MACROS -----------------------------------

#define EXAMPLE_ESP_MAXIMUM_RETRY (5U)
#define DEFAULT_SCAN_LIST_SIZE    (16U)

//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
/**
 * @brief private function for driver init
 *
 * @return esp_err_t an enum err value
 */
static esp_err_t _wifi_driver_init(void);

/**
 * @brief private function for connecting
 *
 * @return esp_err_t an enum err value
 */
static esp_err_t _wifi_driver_connect(void);

/**
 * @brief private function for disconnecting
 *
 * @return esp_err_t an enum err value
 */
static esp_err_t _wifi_driver_disconnect(void);

/**
 * @brief private function for scanning wifi networks
 *
 * @return esp_err_t an enum err value
 */
static esp_err_t _wifi_driver_scan(void);

/**
 * @brief private function for provisioning in BLE mode
 *
 * @param b_is_provisioned pointer to a bool value
 * @return esp_err_t an enum err value
 */
static esp_err_t _wifi_driver_provision_ble();

/**
 * @brief private function for init of provisioning manager
 *
 * @return esp_err_t an enum err value
 */
static esp_err_t _wifi_driver_prov_mgr_init(void);

/**
 * @brief private function for setting up the station mode
 *
 * @return esp_err_t an enum err value
 */
static esp_err_t _wifi_driver_setup_sta(void);

/**
 * @brief a private function fo getting the device name through mac address
 *
 * @param service_name - buffer for the resulting string name
 * @param max - max amount bytes to be in the string
 */
static void _wifi_driver_get_device_service_name(char *service_name, size_t max);

static esp_err_t _wifi_driver_is_prov_mgr_provisioned(bool *pb_is_provisioned);

/**
 * @brief private function that handles events
 *
 * @param p_arg - pointer to an argument
 * @param event_base - enum type of the event
 * @param event_id - id of the event
 * @param p_event_data - pointer to a variable that serves as context
 */
static void _wifi_driver_event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data);

//------------------------- STATIC DATA & CONSTANTS ---------------------------
static EventGroupHandle_t           p_sta_wifi_event_group;
static int                          s_retry_num = 0;
static const char                  *TAG         = "wifi driver";
static const char                  *TAG_PROV    = "provision";
static const char                  *TAG_SCAN    = "scan";
static esp_event_handler_instance_t instance_any_id;
static esp_event_handler_instance_t instance_got_ip;
static volatile bool                b_is_wanted_disconnect;
static volatile bool                b_is_connected   = false;
static wifi_on_status_changed_cb_t  p_wifi_status_cb = NULL;

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
esp_err_t wifi_driver_init(void)
{
    esp_err_t err = _wifi_driver_init();

    if(ESP_OK != err)
    {
        ESP_LOGI(TAG, "WiFi driver initialization in STATION mode FAILED.");
    }

    return err;
}

esp_err_t wifi_driver_connect(void)
{
    return _wifi_driver_connect();
}

esp_err_t wifi_driver_disconnect(void)
{
    return _wifi_driver_disconnect();
}

esp_err_t wifi_driver_scan(void)
{

    return _wifi_driver_scan();
}

esp_err_t wifi_driver_provision_ble(void)
{
    return _wifi_driver_provision_ble();
}

esp_err_t wifi_driver_is_prov_mgr_provisioned(bool *pb_is_provisioned)
{
    return _wifi_driver_is_prov_mgr_provisioned(pb_is_provisioned);
}

bool wifi_driver_is_wifi_connected()
{
    return b_is_connected;
}

void wifi_driver_provision_stop(void)
{
    wifi_prov_mgr_stop_provisioning();
}

void wifi_driver_register_on_status_changed(wifi_on_status_changed_cb_t callback)
{
    p_wifi_status_cb = callback;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
static esp_err_t _wifi_driver_init(void)
{
    // Initialize NVS
    esp_err_t err = nvs_flash_init();

    /* when there is not enough space or some other error occured */
    if(ESP_OK != err)
    {
        err = nvs_flash_erase();
    }

    if(ESP_OK == err)
    {
        err = nvs_flash_init();
    }

    p_sta_wifi_event_group = xEventGroupCreate();

    if(NULL == p_sta_wifi_event_group)
    {
        err = ESP_FAIL;
    }
    if(ESP_OK == err)
    {
        err = esp_netif_init();
    }
    if(ESP_OK == err)
    {
        err = esp_event_loop_create_default();
    }

    if(ESP_OK == err)
    {
        err = esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &_wifi_driver_event_handler, NULL);
    }
    if(ESP_OK == err)
    {
        err = esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &_wifi_driver_event_handler, NULL, &instance_any_id);
    }

    if(ESP_OK == err)
    {
        err = esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &_wifi_driver_event_handler, NULL, &instance_got_ip);
    }

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    if(ESP_OK == err)
    {
        err = esp_wifi_init(&cfg);
    }

    if(ESP_OK == err)
    {
        err = esp_wifi_set_storage(WIFI_STORAGE_RAM);
    }

    /* station mode related init */
    if(ESP_OK == err)
    {
        err = _wifi_driver_setup_sta();
    }

    return err;
}

static esp_err_t _wifi_driver_setup_sta(void)
{
    esp_err_t err = ESP_OK;

    esp_netif_t *sta_netif = NULL;

    sta_netif = esp_netif_create_default_wifi_sta();

    if(NULL == sta_netif)
    {
        err = ESP_FAIL;
    }

    if(ESP_OK == err)
    {
        err = esp_wifi_set_mode(WIFI_MODE_STA);
    }

    return err;
}

static esp_err_t _wifi_driver_connect(void)
{
    esp_err_t err = ESP_OK;

    if(ESP_OK == err)
    {
        err = esp_wifi_start();
    }

    if(ESP_OK == err)
    {
        err = esp_wifi_connect();
    }

    return err;
}

static esp_err_t _wifi_driver_disconnect(void)
{
    b_is_wanted_disconnect = true;
    return esp_wifi_disconnect();
}

static esp_err_t _wifi_driver_scan(void)
{
    esp_err_t err = ESP_OK;

    uint16_t         number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t         ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    err = esp_wifi_scan_start(NULL, true);

    if(ESP_OK == err)
    {
        /* number sets the maximum number of APs that ap_info will hold */
        err = esp_wifi_scan_get_ap_records(&number, ap_info);
    }
    if(ESP_OK == err)
    {
        err = esp_wifi_scan_get_ap_num(&ap_count);
    }
    if(ESP_OK == err)
    {
        ESP_LOGI(TAG_SCAN, "Total APs scanned = %u", ap_count);
        for(int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++)
        {
            ESP_LOGI(TAG_SCAN, "SSID \t\t%s", ap_info[i].ssid);
        }
    }
    return err;
}

static esp_err_t _wifi_driver_is_prov_mgr_provisioned(bool *pb_is_provisioned)
{
    return wifi_prov_mgr_is_provisioned(pb_is_provisioned);
}

static esp_err_t _wifi_driver_provision_ble()
{
    esp_err_t err = _wifi_driver_prov_mgr_init();

    if(ESP_OK == err)
    {
        ESP_LOGI(TAG_PROV, "Starting provisioning...");

        char service_name[12];
        _wifi_driver_get_device_service_name(service_name, sizeof(service_name));
        const char *service_key = "password";

        wifi_prov_security_t security = WIFI_PROV_SECURITY_1;
        /* PROOF OF POSSESION */
        const char *pop = "abcd1234";

        err = wifi_prov_mgr_start_provisioning(security, pop, service_name, service_key);
    }

    return err;
}

static esp_err_t _wifi_driver_prov_mgr_init(void)
{
    // clang-format off
    wifi_prov_mgr_config_t config = {
            .scheme = wifi_prov_scheme_ble,
            .scheme_event_handler = WIFI_PROV_SCHEME_BLE_EVENT_HANDLER_FREE_BT 
        };
    // clang-format on

    return wifi_prov_mgr_init(config);
}

static void _wifi_driver_get_device_service_name(char *service_name, size_t max)
{
    uint8_t     eth_mac[6];
    const char *ssid_prefix = "PROV_";
    esp_wifi_get_mac(WIFI_IF_STA, eth_mac);
    snprintf(service_name, max, "%s%02X%02X%02X", ssid_prefix, eth_mac[3], eth_mac[4], eth_mac[5]);
}

static void _wifi_driver_event_handler(void *p_arg, esp_event_base_t event_base, int32_t event_id, void *p_event_data)
{
    if(event_base == WIFI_PROV_EVENT)
    {
        switch(event_id)
        {
            case WIFI_PROV_START:
                ESP_LOGI(TAG_PROV, "Provisioning started");
                break;
            case WIFI_PROV_CRED_RECV: {
                wifi_sta_config_t *wifi_sta_cfg = (wifi_sta_config_t *)p_event_data;
                ESP_LOGI(TAG_PROV,
                         "Received Wi-Fi credentials"
                         "\n\tSSID     : %s\n\tPassword : %s",
                         (const char *)wifi_sta_cfg->ssid,
                         (const char *)wifi_sta_cfg->password);
                break;
            }

            case WIFI_PROV_CRED_FAIL: {
                wifi_prov_sta_fail_reason_t *reason = (wifi_prov_sta_fail_reason_t *)p_event_data;
                ESP_LOGE(TAG_PROV,
                         "Provisioning failed!\n\tReason : %s"
                         "\n\tPlease reset to factory and retry provisioning",
                         (*reason == WIFI_PROV_STA_AUTH_ERROR) ? "Wi-Fi station authentication failed" : "Wi-Fi access-point not found");
                break;
            }

            case WIFI_PROV_CRED_SUCCESS:
                ESP_LOGI(TAG_PROV, "Provisioning successful");
                break;

            case WIFI_PROV_END:
                /* De-initialize manager once provisioning is finished */
                wifi_prov_mgr_deinit();
                break;
            default:
                break;
        }
    }
    if((WIFI_EVENT == event_base) && (WIFI_EVENT_STA_START == event_id))
    {
        ESP_LOGI(TAG, "WiFi started.");
        if(NULL != p_wifi_status_cb)
        {
            p_wifi_status_cb(WIFI_CONNECTION_STATUS_UNKNOWN);
        }
    }
    else if((IP_EVENT == event_base) && (IP_EVENT_STA_GOT_IP == event_id))
    {
        ip_event_got_ip_t *p_event = (ip_event_got_ip_t *)p_event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&p_event->ip_info.ip));
        s_retry_num = 0;
        ESP_LOGI(TAG, "Connected.");
        b_is_connected = true;
        if(NULL != p_wifi_status_cb)
        {
            p_wifi_status_cb(WIFI_CONNECTION_STATUS_CONNECTED);
        }
    }
    else if((WIFI_EVENT == event_base) && (WIFI_EVENT_STA_CONNECTED == event_id))
    {

        if(NULL != p_wifi_status_cb)
        {
            p_wifi_status_cb(WIFI_CONNECTION_STATUS_CONNECTING);
        }
    }

    else if((WIFI_EVENT == event_base) && (WIFI_EVENT_STA_DISCONNECTED == event_id))
    {
        b_is_connected = false;
        if(true == b_is_wanted_disconnect)
        {
            ESP_LOGI(TAG, "WiFi successfully disconnected.");
            b_is_wanted_disconnect = false;
            if(NULL != p_wifi_status_cb)
            {
                p_wifi_status_cb(WIFI_CONNECTION_STATUS_DISCONNECTED);
            }
        }
        else if(s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY)
        {

            if(ESP_OK != esp_wifi_connect())
            {
                ESP_LOGE(TAG, "Error occured with reconnecting.");
            }
            s_retry_num++;
            ESP_LOGI(TAG, "retry to connect to the AP");
        }
        else
        {
            /* FAILED TO RECONNECT */
            if(ESP_OK != esp_wifi_stop())
            {
                ESP_LOGE(TAG, "Error occured when stoping the wifi.");
            }

            s_retry_num = 0;
            if(NULL != p_wifi_status_cb)
            {
                p_wifi_status_cb(WIFI_CONNECTION_STATUS_DISCONNECTED);
            }
        }
    }
}

//---------------------------- INTERRUPT HANDLERS -----------------------------
