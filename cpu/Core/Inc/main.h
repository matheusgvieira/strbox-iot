/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CELL_1_BTN_Pin GPIO_PIN_13
#define CELL_1_BTN_GPIO_Port GPIOC
#define CELL_1_BTN_EXTI_IRQn EXTI15_10_IRQn
#define CELL_1_OUT_NEG_Pin GPIO_PIN_0
#define CELL_1_OUT_NEG_GPIO_Port GPIOC
#define CELL_1_VOLTAGE_Pin GPIO_PIN_2
#define CELL_1_VOLTAGE_GPIO_Port GPIOC
#define CELL_1_CURRENT_Pin GPIO_PIN_3
#define CELL_1_CURRENT_GPIO_Port GPIOC
#define CELL_1_DPS_Pin GPIO_PIN_0
#define CELL_1_DPS_GPIO_Port GPIOA
#define CELL_1_DPS_EXTI_IRQn EXTI0_IRQn
#define CELL_1_BUILTIN_LED_Pin GPIO_PIN_5
#define CELL_1_BUILTIN_LED_GPIO_Port GPIOA
#define CELL_1_DBG3_Pin GPIO_PIN_10
#define CELL_1_DBG3_GPIO_Port GPIOB
#define CELL_1_OUT_POS_Pin GPIO_PIN_9
#define CELL_1_OUT_POS_GPIO_Port GPIOA
#define T_SWDIO_Pin GPIO_PIN_13
#define T_SWDIO_GPIO_Port GPIOA
#define T_SWCLK_Pin GPIO_PIN_14
#define T_SWCLK_GPIO_Port GPIOA
#define CELL_1_DBG2_Pin GPIO_PIN_4
#define CELL_1_DBG2_GPIO_Port GPIOB
#define CELL_1_DBG1_Pin GPIO_PIN_5
#define CELL_1_DBG1_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
