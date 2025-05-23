#ifndef __CD4051_H__
#define __CD4051_H__


#include "main.h"

#define CD4051_CTRC_SET HAL_GPIO_WritePin(CD_4051_C_GPIO_Port, CD_4051_C_Pin, GPIO_PIN_SET)
#define CD4051_CTRC_CLR HAL_GPIO_WritePin(CD_4051_C_GPIO_Port, CD_4051_C_Pin, GPIO_PIN_RESET)
#define CD4051_CTRB_SET HAL_GPIO_WritePin(CD_4051_B_GPIO_Port, CD_4051_B_Pin, GPIO_PIN_SET)
#define CD4051_CTRB_CLR HAL_GPIO_WritePin(CD_4051_B_GPIO_Port, CD_4051_B_Pin, GPIO_PIN_RESET)
#define CD4051_CTRA_SET HAL_GPIO_WritePin(CD_4051_A_GPIO_Port, CD_4051_A_Pin, GPIO_PIN_SET)
#define CD4051_CTRA_CLR HAL_GPIO_WritePin(CD_4051_A_GPIO_Port, CD_4051_A_Pin, GPIO_PIN_RESET)
void CD_4051_SetChannel(u8 channel);
#endif /* __CD4051_H__ */