/*
 * uart_com.c
 *
 *  Created on: Jul 18, 2022
 *      Author: mgois
 */


#include "uart_com.h"
#include <string.h>


char aux[MAX_BUFFER];


void uart_send_data(photovoltaic *cell){

	if (cell->send_uart) {
		sprintf(aux, "V-%f\r\n", cell->voltage);

		HAL_UART_Transmit(&huart3, (uint8_t *)aux, strlen(aux), 100);

		sprintf(aux, "C-%f\r\n", cell->current);

		HAL_UART_Transmit(&huart3, (uint8_t *)aux, strlen(aux), 100);

		sprintf(aux, "P-%f\r\n", cell->power);

		HAL_UART_Transmit(&huart3, (uint8_t *)aux, strlen(aux), 100);

		sprintf(aux, "E-%f\r\n", cell->energy);

		HAL_UART_Transmit(&huart3, (uint8_t *)aux, strlen(aux), 100);
	}
}
