#ifndef _AD_9833_H
#define _AD_9833_H
#include <math.h>
#include "./SYSTEM/sys/sys.h"

// ------------------------- Defines -------------------------
#define AD9833PORT GPIOE      // PORT OF AD9833
#define AD9833DATA GPIO_Pin_7 // SPI DATA PIN
#define AD9833SCK GPIO_Pin_8  // SPI Clock PIN
#define AD9833SS GPIO_Pin_9   // SPI Chip Select
#define ASM_NOP()

#define TRI_WAVE 	0  		//输出三角波
#define SIN_WAVE 	1		//输出正弦波
#define SQU_WAVE 	2		//输出方波
// Assembly NOPE (Little Delay)
enum WaveType{SIN, SQR, TRI}; // Wave Selection Enum

// ------------------ Functions  ---------------------
void AD9833_SetWave(u16 Wave);                      // Sets Output Wave Type
void AD9833_WaveSeting(double Freq,unsigned int Freq_SFR,unsigned int WaveMode,unsigned int Phase ); // Sets Wave Frequency, Phase and Type
void AD9833_Write(unsigned int TxData);              // Writes 16 bits to AD9833
void AD9833_Init(void);                             // Initializes AD9833



#endif