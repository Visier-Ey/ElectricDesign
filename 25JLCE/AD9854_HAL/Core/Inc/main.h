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
#include <stdint.h>
#include <stdio.h>


/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#ifndef u32
typedef uint32_t u32;
#endif
#ifndef u16
typedef uint16_t u16;
#endif
#ifndef u8
typedef uint8_t u8;
#endif
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RD_Pin GPIO_PIN_0
#define RD_GPIO_Port GPIOF
#define WR_Pin GPIO_PIN_1
#define WR_GPIO_Port GPIOF
#define UDCLK_Pin GPIO_PIN_2
#define UDCLK_GPIO_Port GPIOF
#define RST_Pin GPIO_PIN_3
#define RST_GPIO_Port GPIOF
#define SP_Pin GPIO_PIN_4
#define SP_GPIO_Port GPIOF
#define OSK_Pin GPIO_PIN_5
#define OSK_GPIO_Port GPIOF
#define FDATA_Pin GPIO_PIN_6
#define FDATA_GPIO_Port GPIOF
#define SDI_Pin GPIO_PIN_5
#define SDI_GPIO_Port GPIOA
#define SDO_Pin GPIO_PIN_6
#define SDO_GPIO_Port GPIOA
#define IO_RST_Pin GPIO_PIN_7
#define IO_RST_GPIO_Port GPIOA
#define HMC241_A_Pin GPIO_PIN_1
#define HMC241_A_GPIO_Port GPIOB
#define HMC241_B_Pin GPIO_PIN_2
#define HMC241_B_GPIO_Port GPIOB
#define CD_4051_A_Pin GPIO_PIN_10
#define CD_4051_A_GPIO_Port GPIOE
#define CD_4051_B_Pin GPIO_PIN_11
#define CD_4051_B_GPIO_Port GPIOE
#define CD_4051_C_Pin GPIO_PIN_12
#define CD_4051_C_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
