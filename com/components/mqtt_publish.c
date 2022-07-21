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

static const char *TAG = "PUB";

static EventGroupHandle_t s_mqtt_event_group;

extern QueueHandle_t module_queue;

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

void mqtt_publish_module_task(void *pvParameters)
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

    com_module module;

    while (1) {


        EventBits_t EventBits = xEventGroupGetBits(s_mqtt_event_group);

//        ESP_LOGI(TAG, "EventBits=%x", EventBits);

        if (xQueueReceive(module_queue, (void *)&( module ), ( TickType_t ) 0 ) == pdTRUE) {
            if (EventBits & MQTT_CONNECTED_BIT) {

                ESP_LOGI(TAG, "update=[%d]\n", module.update);

                if (module.update) {
                    ESP_LOGI(TAG, "topic=[%s]\n", module.topic_current);
                    ESP_LOGI(TAG, "current=[%.2f]\n", module.current);

                    ESP_LOGI(TAG, "topic=[%s]\n", module.topic_voltage);
                    ESP_LOGI(TAG, "voltage=[%.2f]\n", module.voltage);

                    ESP_LOGI(TAG, "topic=[%s]\n", module.topic_power);
                    ESP_LOGI(TAG, "power=[%.2f]\n", module.power);

                    ESP_LOGI(TAG, "topic=[%s]\n", module.topic_energy);
                    ESP_LOGI(TAG, "energy=[%.2f]\n", module.energy);

                    char payload[50];

                    sprintf(payload, "%f", module.current);
                    esp_mqtt_client_publish(mqtt_client, module.topic_current, payload, strlen(payload), 0, 0);

                    sprintf(payload, "%f", module.voltage);
                    esp_mqtt_client_publish(mqtt_client, module.topic_voltage, payload, strlen(payload), 0, 0);

                    sprintf(payload, "%f", module.power);
                    esp_mqtt_client_publish(mqtt_client, module.topic_power, payload, strlen(payload), 0, 0);

                    sprintf(payload, "%f", module.energy);
                    esp_mqtt_client_publish(mqtt_client, module.topic_energy, payload, strlen(payload), 0, 0);

                    set_init_nvs(&module);
                    module.update = 0;
                }
            } else {
                ESP_LOGE(TAG, "mqtt broker not connect");
            }
        }


    }

    ESP_LOGI(TAG, "Task Delete");
    esp_mqtt_client_stop(mqtt_client);
    vTaskDelete(NULL);
}