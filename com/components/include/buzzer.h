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
    int32_t time;
    int8_t state;
} buzzer;

void init_buzzer(buzzer *buzzer);
void set_state_buzzer(buzzer *led, uint8_t state);
void toggle_buzzer_time(buzzer *buzzer);

#ifdef __cplusplus
}
#endif