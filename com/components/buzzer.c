/* 
    Main Project
    author: Debora Fernandes e Matheus Gois
    description: Control occhi
*/

#include <stdio.h>
#include "buzzer.h"

static const char *TAG = "BUZZER OCCHI";

void set_state_buzzer(buzzer *buzzer, uint8_t state)
{   
    buzzer -> state = state;
    gpio_set_level(buzzer->pin, state); /* Set the GPIO level according to the state (LOW or HIGH)*/
}

void toggle_buzzer_time(buzzer *buzzer) {
    buzzer -> state = 1;
    gpio_set_level(buzzer->pin, 1);
    vTaskDelay(buzzer->time / portTICK_PERIOD_MS);

    buzzer -> state = 0;
    gpio_set_level(buzzer->pin, 0);
    vTaskDelay(buzzer->time / portTICK_PERIOD_MS);
}

void init_buzzer(buzzer *buzzer)
{
    ESP_LOGI(TAG, "Configured GPIO Buzzer!");

    gpio_reset_pin(buzzer -> pin);
    gpio_set_direction(buzzer -> pin, GPIO_MODE_OUTPUT); /* Set the GPIO as a push/pull output */
}
