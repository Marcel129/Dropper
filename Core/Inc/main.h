/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "dropper.h"
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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define SENSOR_9_Pin GPIO_PIN_2
#define SENSOR_9_GPIO_Port GPIOC
#define SENSOR_10_Pin GPIO_PIN_3
#define SENSOR_10_GPIO_Port GPIOC
#define STEPPER1_EN_Pin GPIO_PIN_0
#define STEPPER1_EN_GPIO_Port GPIOA
#define STEPPER1_DIR_Pin GPIO_PIN_1
#define STEPPER1_DIR_GPIO_Port GPIOA
#define LPUART1_TX_Pin GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA
#define SENSOR_12_Pin GPIO_PIN_4
#define SENSOR_12_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define SENSOR_11_Pin GPIO_PIN_0
#define SENSOR_11_GPIO_Port GPIOB
#define RELAY_13_Pin GPIO_PIN_1
#define RELAY_13_GPIO_Port GPIOB
#define RELAY_12_Pin GPIO_PIN_2
#define RELAY_12_GPIO_Port GPIOB
#define RELAY_5_Pin GPIO_PIN_10
#define RELAY_5_GPIO_Port GPIOB
#define RELAY_11_Pin GPIO_PIN_11
#define RELAY_11_GPIO_Port GPIOB
#define SENSOR_7_Pin GPIO_PIN_12
#define SENSOR_7_GPIO_Port GPIOB
#define RELAY_16_Pin GPIO_PIN_13
#define RELAY_16_GPIO_Port GPIOB
#define RELAY_15_Pin GPIO_PIN_14
#define RELAY_15_GPIO_Port GPIOB
#define RELAY_14_Pin GPIO_PIN_15
#define RELAY_14_GPIO_Port GPIOB
#define RELAY_10_Pin GPIO_PIN_6
#define RELAY_10_GPIO_Port GPIOC
#define STEPPER2_DIR_Pin GPIO_PIN_7
#define STEPPER2_DIR_GPIO_Port GPIOC
#define RELAY_9_Pin GPIO_PIN_8
#define RELAY_9_GPIO_Port GPIOC
#define RELAY_1_Pin GPIO_PIN_9
#define RELAY_1_GPIO_Port GPIOC
#define RELAY_4_Pin GPIO_PIN_8
#define RELAY_4_GPIO_Port GPIOA
#define RELAY_3_Pin GPIO_PIN_9
#define RELAY_3_GPIO_Port GPIOA
#define RELAY_8_Pin GPIO_PIN_10
#define RELAY_8_GPIO_Port GPIOA
#define SENSOR_6_Pin GPIO_PIN_11
#define SENSOR_6_GPIO_Port GPIOA
#define SENSOR_5_Pin GPIO_PIN_12
#define SENSOR_5_GPIO_Port GPIOA
#define SENSOR_3_Pin GPIO_PIN_10
#define SENSOR_3_GPIO_Port GPIOC
#define SENSOR_3_EXTI_IRQn EXTI15_10_IRQn
#define SENSOR_1_Pin GPIO_PIN_11
#define SENSOR_1_GPIO_Port GPIOC
#define SENSOR_1_EXTI_IRQn EXTI15_10_IRQn
#define SENSOR_2_Pin GPIO_PIN_12
#define SENSOR_2_GPIO_Port GPIOC
#define SENSOR_2_EXTI_IRQn EXTI15_10_IRQn
#define SENSOR_4_Pin GPIO_PIN_2
#define SENSOR_4_GPIO_Port GPIOD
#define SENSOR_4_EXTI_IRQn EXTI2_IRQn
#define T_SWO_Pin GPIO_PIN_3
#define T_SWO_GPIO_Port GPIOB
#define RELAY_6_Pin GPIO_PIN_4
#define RELAY_6_GPIO_Port GPIOB
#define RELAY_7_Pin GPIO_PIN_5
#define RELAY_7_GPIO_Port GPIOB
#define STEPPER2_EN_Pin GPIO_PIN_6
#define STEPPER2_EN_GPIO_Port GPIOB
#define SENSOR_8_Pin GPIO_PIN_7
#define SENSOR_8_GPIO_Port GPIOB
#define RELAY_2_Pin GPIO_PIN_9
#define RELAY_2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
