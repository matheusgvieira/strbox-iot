/*
 * uart_com.h
 *
 *  Created on: Jul 18, 2022
 *      Author: mgois
 */

#ifndef INC_UART_COM_H_
#define INC_UART_COM_H_

#include "structs.h"
#include <strings.h>
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 100
#define UART_CODE_VOLTAGE "V-"
#define UART_CODE_CURRENT "C-"
#define UART_CODE_POWER "P-"
#define UART_CODE_ENERGY "E-"

#ifdef __cplusplus
extern "C" {
#endif


void uart_send_data(photovoltaic *cell);
#ifdef __cplusplus
}
#endif

#endif /* INC_UART_COM_H_ */
