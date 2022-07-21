#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_log.h"
#include "esp_event.h"
#include "mqtt_client.h"
#include "driver/twai.h"

#include "mqtt.h"

static const char *TAG = "PUB_STATE";

static EventGroupHandle_t s_mqtt_event_group;

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            xEventGroupSetBits(s_mqtt_event_group, MQTT_CONNECTED_BIT);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGW(TAG, "MQTT_EVENT_DISCONNECTED");
            xEventGroupClearBits(s_mqtt_event_group, MQTT_CONNECTED_BIT);
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
    return ESP_OK;
}

void mqtt_publish_state_task(void *pvParameters)
{
    ESP_LOGI(TAG, "Start Publish Broker:%s", CONFIG_BROKER_URL);

    const esp_mqtt_client_config_t mqtt_cfg = {
            .uri = CONFIG_BROKER_URL,
            .event_handle = mqtt_event_handler,
            .username = "Token #2",
            .password = "a6fbba72-067c-4309-be80-ac15ec1c1aa7"
    };

    s_mqtt_event_group = xEventGroupCreate();
    esp_mqtt_client_handle_t mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    xEventGroupClearBits(s_mqtt_event_group, MQTT_CONNECTED_BIT);
    esp_mqtt_client_start(mqtt_client);
    xEventGroupWaitBits(s_mqtt_event_group, MQTT_CONNECTED_BIT, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connect to MQTT Server");

    mqtt_message_t message = *(mqtt_message_t *) pvParameters;

    while (1) {
        ESP_LOGI(TAG, "topic=[%s]\n", message.topic);
        ESP_LOGI(TAG, "data=[%.2f]\n", message.payload);

        EventBits_t EventBits = xEventGroupGetBits(s_mqtt_event_group);

        ESP_LOGI(TAG, "EventBits=%x", EventBits);

        if (EventBits & MQTT_CONNECTED_BIT) {
            char payload[50];
            sprintf(payload, "%f", message.payload);
            esp_mqtt_client_publish(mqtt_client, message.topic, payload, strlen(payload), 0, 0);
        } else {
            ESP_LOGE(TAG, "mqtt broker not connect");
        }

        if(strcmp(message.tag, "current_state") == 0) {
            vTaskDelay( 10000 / portTICK_PERIOD_MS);
        }
    }

    ESP_LOGI(TAG, "Task Delete");
    esp_mqtt_client_stop(mqtt_client);
    vTaskDelete(NULL);
}