#ifndef _AD9959_H
#define _AD9959_H

#include "main.h"

#define uchar unsigned char
#define uint unsigned int 

// HAL_GPIO_WritePin(GPIOx, GPIO_PIN_x, GPIO_PIN_SET);
//AD998 I/O��������

//�˿�C�궨��
#define SCLK_1 HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_SET)
#define SCLK_0 HAL_GPIO_WritePin(SCLK_GPIO_Port, SCLK_Pin, GPIO_PIN_RESET)

#define CS_1 HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)
#define CS_0 HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)

#define IO_update_1 HAL_GPIO_WritePin(IO_UP_GPIO_Port, IO_UP_Pin, GPIO_PIN_SET)
#define IO_update_0 HAL_GPIO_WritePin(IO_UP_GPIO_Port, IO_UP_Pin, GPIO_PIN_RESET)

#define SDIO0_1 HAL_GPIO_WritePin(SD0_GPIO_Port, SD0_Pin, GPIO_PIN_SET)
#define SDIO0_0 HAL_GPIO_WritePin(SD0_GPIO_Port, SD0_Pin, GPIO_PIN_RESET)

#define PS0_1 HAL_GPIO_WritePin(P0_GPIO_Port, P0_Pin, GPIO_PIN_SET)
#define PS0_0 HAL_GPIO_WritePin(P0_GPIO_Port, P0_Pin, GPIO_PIN_RESET)

#define PS1_1 HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, GPIO_PIN_SET)
#define PS1_0 HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, GPIO_PIN_RESET)

#define PS2_1 HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, GPIO_PIN_SET)
#define PS2_0 HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, GPIO_PIN_RESET)

#define PS3_1 HAL_GPIO_WritePin(P3_GPIO_Port, P3_Pin, GPIO_PIN_SET)
#define PS3_0 HAL_GPIO_WritePin(P3_GPIO_Port, P3_Pin, GPIO_PIN_RESET)

//�˿�A�궨��
#define SDIO1_1 HAL_GPIO_WritePin(SD1_GPIO_Port, SD1_Pin, GPIO_PIN_SET)
#define SDIO1_0 HAL_GPIO_WritePin(SD1_GPIO_Port, SD1_Pin, GPIO_PIN_RESET)

#define SDIO2_1 HAL_GPIO_WritePin(SD2_GPIO_Port, SD2_Pin, GPIO_PIN_SET)
#define SDIO2_0 HAL_GPIO_WritePin(SD2_GPIO_Port, SD2_Pin, GPIO_PIN_RESET)

#define SDIO3_1 HAL_GPIO_WritePin(SD3_GPIO_Port, SD3_Pin, GPIO_PIN_SET)	
#define SDIO3_0 HAL_GPIO_WritePin(SD3_GPIO_Port, SD3_Pin, GPIO_PIN_RESET)

#define PWR_1  HAL_GPIO_WritePin(PW_D_GPIO_Port, PW_D_Pin, GPIO_PIN_SET)
#define PWR_0 HAL_GPIO_WritePin(PW_D_GPIO_Port, PW_D_Pin, GPIO_PIN_RESET)

#define Reset_1 HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)
#define Reset_0 HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)


//-----------------------------------------------------------------
// �ⲿ��������
//-----------------------------------------------------------------
extern void GPIO_AD9959_Configuration(void)  ;//I/O�˿�����
extern void AD9959_Init(void);  //��λ
extern void WrFrequencyTuningWorddata(double f,uchar *ChannelFrequencyTuningWorddata);
extern void IO_update(void)  ;
extern void WriteToAD9959ViaSpi(uchar RegisterAddress, uchar NumberofRegisters, uchar *RegisterData,uchar temp) ;
extern void WrPhaseOffsetTuningWorddata(double f,uchar *ChannelPhaseOffsetTuningWorddata);
extern void WrAmplitudeTuningWorddata(double f,uchar *ChannelAmplitudeTuningWorddata);//�������ע�������Ƶ������
extern void WrAmplitudeTuningWorddata1(double f,uchar *ChannelAmplitudeTuningWorddata,uchar *ASRAmplituteWordata);

#endif
