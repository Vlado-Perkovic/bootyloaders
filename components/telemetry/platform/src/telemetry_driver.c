/**
 * @file telemetry_driver.c
 *
 * @brief
 *
 * COPYRIGHT NOTICE: (c) 2023 Byte Lab Grupa d.o.o.
 * All rights reserved.
 */

//--------------------------------- INCLUDES ----------------------------------
#include "telemetry_driver.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "mqtt_client.h"

//---------------------------------- MACROS -----------------------------------
#define BROKER     "mqtt://4gpc.l.time4vps.cloud"
#define TOPIC      "WES/Neptune/game"
#define TOPIC_SEND "WES/Neptune/sensors"
//-------------------------------- DATA TYPES ---------------------------------

//---------------------- PRIVATE FUNCTION PROTOTYPES --------------------------
static esp_err_t _telemetry_driver_init(void);

static esp_err_t _telemetry_driver_connection_status_update(const char *p_msg);

static void _mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

//------------------------- STATIC DATA & CONSTANTS ---------------------------

static const char                   *TAG                           = "MQTT_EXAMPLE";
static esp_mqtt_client_handle_t      p_client                      = NULL;
static telemetry_on_new_message_cb_t p_telemetry_on_new_message_cb = NULL;

//------------------------------- GLOBAL DATA ---------------------------------

//------------------------------ PUBLIC FUNCTIONS -----------------------------
esp_err_t telemetry_driver_init(void)
{
    return _telemetry_driver_init();
}

esp_err_t telemetry_driver_connection_status_update(const char *p_msg)
{
    return _telemetry_driver_connection_status_update(p_msg);
}

void telemetry_driver_register_on_new_message(telemetry_on_new_message_cb_t p_cbk)
{
    /* if the p_cbk == NULL then it just unregisters the callback */
    p_telemetry_on_new_message_cb = p_cbk;
}
//---------------------------- PRIVATE FUNCTIONS ------------------------------
static esp_err_t _telemetry_driver_init(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = BROKER,
    };
    esp_err_t err = ESP_OK;

    p_client = esp_mqtt_client_init(&mqtt_cfg);
    if(NULL == p_client)
    {
        err = ESP_FAIL;
    }

    if(ESP_OK == err)
    {
        err = esp_mqtt_client_register_event(p_client, ESP_EVENT_ANY_ID, _mqtt_event_handler, NULL);
    }

    if(ESP_OK == err)
    {
        err = esp_mqtt_client_start(p_client);
    }
    return err;
}

static esp_err_t _telemetry_driver_connection_status_update(const char *p_msg)
{
    esp_err_t err = ESP_OK;

    int msg_id = esp_mqtt_client_publish(p_client, TOPIC_SEND, p_msg, 0, 0, 0);
    if(0 > msg_id)
    {
        ESP_LOGI(TAG, "sent publish failed, msg_id=%d", msg_id);

        err = ESP_FAIL;
    }
    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
    }

    return err;
}

esp_err_t telemetry_driver_send(const char* topic, const char *p_msg) {
    esp_err_t err = ESP_OK;

    int msg_id = esp_mqtt_client_publish(p_client, topic, p_msg, 0, 0, 0);
    if(0 > msg_id)
    {
        ESP_LOGI(TAG, "sent publish failed, msg_id=%d", msg_id);

        err = ESP_FAIL;
    }
    if(ESP_OK == err)
    {
        ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
    }

    return err;
}


static void _mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t  p_event        = event_data;
    esp_mqtt_client_handle_t p_event_client = p_event->client;
    int                      msg_id;
    switch((esp_mqtt_event_id_t)event_id)
    {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");

            msg_id = esp_mqtt_client_subscribe(p_event_client, TOPIC, 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", p_event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", p_event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", p_event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            if(NULL != p_telemetry_on_new_message_cb)
            {
                p_telemetry_on_new_message_cb(p_event->data);
            }
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");

            break;
        default:
            ESP_LOGI(TAG, "Other p_event id:%d", p_event->event_id);
            break;
    }
}
//---------------------------- INTERRUPT HANDLERS -----------------------------
