#ifndef ANALYSIS_CMD_H
#define ANALYSIS_CMD_H
#include "AD9854.h"
// ! PROTOCOL HEADER
// the first byte idenetify the command
// the second check the legitimacy

#define CMD_HEADER 0x05
#define END 0xfe
#define FREQ 0xee
#define VOUT 0xef
#define SWEEP 0xde
#define AMP 0xdd

extern uint16_t freq;
extern uint16_t Vout;
extern uint16_t amp;
extern uint8_t sweep;
float calc_gain(int frequ){
	return 6.872*(frequ  - 100)/100 + 750;
}

const float output_voltage[64] = {200.00f,   //  0.0 dB  → 200.00 mV
  188.82f,   // -0.5 dB  → 188.82 mV
  178.26f,   // -1.0 dB  → 178.26 mV
  168.28f,   // -1.5 dB  → 168.28 mV
  158.86f,   // -2.0 dB  → 158.86 mV
  150.00f,   // -2.5 dB  → 150.00 mV
  141.58f,   // -3.0 dB  → 141.58 mV
  133.66f,   // -3.5 dB  → 133.66 mV
  126.20f,   // -4.0 dB  → 126.20 mV
  119.14f,   // -4.5 dB  → 119.14 mV
  112.46f,   // -5.0 dB  → 112.46 mV
  106.18f,   // -5.5 dB  → 106.18 mV
  100.24f,   // -6.0 dB  → 100.24 mV
  94.64f,    // -6.5 dB  →  94.64 mV
  89.34f,    // -7.0 dB  →  89.34 mV
  84.34f,    // -7.5 dB  →  84.34 mV
  79.62f,    // -8.0 dB  →  79.62 mV
  75.16f,    // -8.5 dB  →  75.16 mV
  70.96f,    // -9.0 dB  →  70.96 mV
  67.00f,    // -9.5 dB  →  67.00 mV
  63.24f,    // -10.0 dB →  63.24 mV 3162f
  59.70f,    // -10.5 dB →  59.70 mV
  56.36f,    // -11.0 dB →  56.36 mV
  53.22f,    // -11.5 dB →  53.22 mV
  50.24f,    // -12.0 dB →  50.24 mV
  47.42f,    // -12.5 dB →  47.42 mV
  44.78f,    // -13.0 dB →  44.78 mV
  42.26f,    // -13.5 dB →  42.26 mV
  39.90f,    // -14.0 dB →  39.90 mV
  37.68f,    // -14.5 dB →  37.68 mV
  35.56f,    // -15.0 dB →  35.56 mV
  33.58f,    // -15.5 dB →  33.58 mV
  31.70f,    // -16.0 dB →  31.70 mV 
  29.92f,    // -16.5 dB →  29.92 mV 
  28.26f,    // -17.0 dB →  28.26 mV
  26.68f,    // -17.5 dB →  26.68 mV
  25.18f,    // -18.0 dB →  25.18 mV
  23.78f,    // -18.5 dB →  23.78 mV
  22.44f,    // -19.0 dB →  22.44 mV
  21.18f,    // -19.5 dB →  21.18 mV
  20.00f,    // -20.0 dB →  20.00 mV
  18.88f,    // -20.5 dB →  18.88 mV
  17.82f,    // -21.0 dB →  17.82 mV
  16.82f,    // -21.5 dB →  16.82 mV
  15.88f,    // -22.0 dB →  15.88 mV
  15.00f,    // -22.5 dB →  15.00 mV
  14.16f,    // -23.0 dB →  14.16 mV
  13.36f,    // -23.5 dB →  13.36 mV
  12.62f,    // -24.0 dB →  12.62 mV
  11.92f,    // -24.5 dB →  11.92 mV
  11.24f,    // -25.0 dB →  11.24 mV
  10.62f,    // -25.5 dB →  10.62 mV
  10.02f,    // -26.0 dB →  10.02 mV
  9.46f,     // -26.5 dB →   9.46 mV
  8.94f,     // -27.0 dB →   8.94 mV
  8.44f,     // -27.5 dB →   8.44 mV
  7.96f,     // -28.0 dB →   7.96 mV
  7.52f,     // -28.5 dB →   7.52 mV
  7.10f,     // -29.0 dB →   7.10 mV
  6.70f,     // -29.5 dB →   6.70 mV
  6.32f,     // -30.0 dB →   6.32 mV
  5.98f,     // -30.5 dB →   5.98 mV
  5.64f,     // -31.0 dB →   5.64 mV
  5.32f      // -31.5 dB →   5.32 mV
};

// get 9854 gain and attenuator , param is freq and Vout
void calc_Vol(u16 freq, u16 Vout, int* gain, int* att) {
    float g = calc_gain(freq);  // 假设 calc_gain 已定义

    if (Vout <= 50) {
        *att = (int)(63 - (Vout / 50.0) * 39);  
        *gain = (int)g;  
    } else {
        *att = 24;
        *gain = (int)(43.7663 * (Vout - 50) + g); 
    }
}

void SendFreq(u16 freq){
    u8* data= (u8*)&freq;
		u8 header =CMD_HEADER;
		u8 end = END;
		printf("%c",header);
    printf("%c",data[0]);
    printf("%c",data[1]);
		printf("%c",end);
}

void AnalysisCmd(u8* payload){
    u16* data= (u16*)(payload+1);
    if (payload[0]==FREQ) {
			freq = (*data) * 100;
			SendFreq(*data);
		}
    if (payload[0]==AMP){
       amp = *data;
      //  ConvertAmplitude(amp);
      }
    if (payload[0]==VOUT) Vout = *data;
		if (payload[0]==SWEEP) sweep = 1 - sweep;
}

void ConvertAmplitude(u16* amp){
  u16 _amp = (u16)(*amp / 40.0 * 4095.0);
  amp = &_amp;
  printf("%d",(int)amp);
}

#endif
