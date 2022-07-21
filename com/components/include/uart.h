#pragma once

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "structures.h"

#ifdef __cplusplus
extern "C" {
#endif

// Defines
#define TXD_PIN (GPIO_NUM_17)
#define RXD_PIN (GPIO_NUM_16)

#define UART UART_NUM_2
#define RX_BUF_SIZE 1024

// Variables

// Functions
void initialization_uart(void);
void read_byte_uart(void *pvParameters);
void writeByteUart(int8_t select_relay, int8_t value);
//void echo_task(void *arg);


#ifdef __cplusplus
}
#endif