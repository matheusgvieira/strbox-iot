#pragma once

#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#ifdef __cplusplus
extern "C" {
#endif

// Structure of sensor
typedef struct {
	gpio_num_t pin;
    char* color;
} led_rgb;

void init_led(led_rgb *led);
void set_state_led(led_rgb *led, uint8_t state);
void toggle_led(led_rgb *led, TickType_t time);

#ifdef __cplusplus
}
#endif