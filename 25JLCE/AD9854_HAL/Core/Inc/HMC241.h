#ifndef __HMC241_H__
#define __HMC241_H__

#include "main.h"

#define HMC241_CTRLA_SET HAL_GPIO_WritePin(HMC241_A_GPIO_Port, HMC241_A_Pin, GPIO_PIN_SET)
#define HMC241_CTRLB_SET HAL_GPIO_WritePin(HMC241_B_GPIO_Port, HMC241_B_Pin, GPIO_PIN_SET)
#define HMC241_CTRLA_CLR HAL_GPIO_WritePin(HMC241_A_GPIO_Port, HMC241_A_Pin, GPIO_PIN_RESET)
#define HMC241_CTRLB_CLR HAL_GPIO_WritePin(HMC241_B_GPIO_Port, HMC241_B_Pin, GPIO_PIN_RESET)


void HMC241_Set_Channel(u8 channel); // channel = 1~4
// void HMC241_Set_Channel_B(u8 channel);

#endif 