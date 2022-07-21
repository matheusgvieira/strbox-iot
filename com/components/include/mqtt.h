#pragma once

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "wifi.h"
#include "mqtt_client.h"
#include "structures.h"
#include "led.h"
#include "uart.h"

#ifdef __cplusplus
extern "C" {
#endif

// Defines
#define TAG_MQTT "MQTT"
#define CONFIG_BROKER_URL "mqtt://mqtt.tago.io:1883"
#define MQTT_CONNECTED_BIT BIT0

// Structs
typedef struct {
    char* topic;
    float payload;
    char* tag;
    int8_t payload_received;
    gpio_num_t pin_relay;
} mqtt_message_t;


// Variables

// Functions
void mqtt_init(void);
void mqtt_subscriber_task(void *pvParameters);
void mqtt_subscriber_rele2_task(void *pvParameters);
void mqtt_publish_state_task(void *pvParameters);
void mqtt_publish_module_task(void *pvParameters);

#ifdef __cplusplus
}
#endif