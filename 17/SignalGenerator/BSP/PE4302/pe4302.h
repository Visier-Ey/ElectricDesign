#ifndef __PE4302_H__
#define __PE4302_H__

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"

#define SERIAL_LE PBout(10) // Serial LE pin
#define SERIAL_CLK PBout(11) // Serial CLK pin
#define SERIAL_DATA PBout(12) // Serial Data pin

void PE4302_Init(void); // Initialize PE4302
void PE4302_Set_Attenuation(u8 attenuation); // Set attenuation value (0-31 dB)

#endif