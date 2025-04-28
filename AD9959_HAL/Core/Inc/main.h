/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define P3_Pin GPIO_PIN_2
#define P3_GPIO_Port GPIOE
#define IO_UP_Pin GPIO_PIN_3
#define IO_UP_GPIO_Port GPIOE
#define NC_Pin GPIO_PIN_4
#define NC_GPIO_Port GPIOE
#define SCLK_Pin GPIO_PIN_5
#define SCLK_GPIO_Port GPIOE
#define CS_Pin GPIO_PIN_6
#define CS_GPIO_Port GPIOE
#define SD1_Pin GPIO_PIN_13
#define SD1_GPIO_Port GPIOC
#define SD0_Pin GPIO_PIN_0
#define SD0_GPIO_Port GPIOF
#define SD3_Pin GPIO_PIN_1
#define SD3_GPIO_Port GPIOF
#define SD2_Pin GPIO_PIN_2
#define SD2_GPIO_Port GPIOF
#define PW_D_Pin GPIO_PIN_3
#define PW_D_GPIO_Port GPIOF
#define RST_Pin GPIO_PIN_4
#define RST_GPIO_Port GPIOF
#define P0_Pin GPIO_PIN_9
#define P0_GPIO_Port GPIOB
#define P1_Pin GPIO_PIN_0
#define P1_GPIO_Port GPIOE
#define P2_Pin GPIO_PIN_1
#define P2_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
