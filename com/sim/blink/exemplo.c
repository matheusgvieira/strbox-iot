#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "led.h"

led_rgb led_2 = {.pin = 21, .color = "red"};

void app_main(void)
{
    init_led(&led_2);

    while (1)
    {
        printf("Projeto Occhi ON\n");
        set_state_led(&led_2, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        printf("Projeto Occhi OFF\n");
        set_state_led(&led_2, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}