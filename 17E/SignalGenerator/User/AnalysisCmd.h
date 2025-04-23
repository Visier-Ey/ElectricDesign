#ifndef ANALYSIS_CMD_H
#define ANALYSIS_CMD_H
#include "AD9854.h"
#include "math.h"
// ! PROTOCOL HEADER
// the first byte idenetify the command
// the second check the legitimacy

#define CMD_HEADER 0x05
#define END 0xfe
#define FREQ 0xee
#define FAST_SWEEP 0xaa
#define VOUT 0xef
#define SWEEP 0xde
#define AMP 0xdd

extern uint16_t freq;
extern uint16_t Vout;
extern uint16_t amp;
extern uint8_t sweep;
extern uint8_t fast_sweep;
//float calc_gain(int frequ){
//	return 6.872*(frequ  - 100)/100 + 750;
//}


// get 9854 gain and attenuator , param is freq and Vout
void calc_Vol(u16 freq, u16 Vout, int* gain, int* att) {
//    float g = calc_gain(freq);  // 假设 calc_gain 已定义
		
		if(Vout<=5){
			*att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/7))+10;  
        *gain = 200;  
		}
		else if(Vout==6){
			*att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/8))+10;  
        *gain = 200;  
		}
		else if(Vout==7){
			*att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/8))+10;  
        *gain = 220;  
		}
		else if(Vout==8){
			*att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/12))+10;  
        *gain = 200;  
		}
		else if(Vout==9){
			*att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/17))+10;  
        *gain = 200;  
		}
		else if (Vout <= 20) {
				Vout = 75*Vout/8 - 51;
        *att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/Vout))+10;  
        *gain = 200;  
    }
		else if (Vout <= 45){
			Vout = 2*Vout - 41;
        *att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/Vout))+10;  
        *gain = 775;  
    }
		else if (Vout <= 60){
			Vout = 16*Vout/10 - 28;
			Vout = 2*Vout - 37;
        *att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/Vout))+10;  
        *gain = 775;  
    }
		else if (Vout <= 70) {
			Vout = 32*Vout/10 - 75;
        *att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/Vout))+10;  
        *gain = 775;  
    }
		else {
				//Vout=164*Vout/100 - 71;
				//Vout=Vout*35/100;
			Vout=574*Vout/1000 - 25;
        *att = (int)(20*log10f((282.26f-0.698f*freq/100.0f)/Vout));
        *gain = 2036; 
    }
    //    *att = (int)(20*log10f((106.5f-0.186f*freq/100.0f)/Vout))+10;  
    //    *gain = 200;  
    //} else {
//				Vout/=2;
//				//Vout=Vout*63/100;
//        *att = (int)(20*log10f((282.26f-0.698f*freq/100.0f)/Vout));
//        *gain = 2036; 
//    }
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

void ConvertAmplitude(u16* gain){
  amp = (u16)((13.865**gain+334.5) / 3300.0 * 4095.0);
//  printf("%d",(int)amp);
}

void AnalysisCmd(u8* payload){
    u16* data= (u16*)(payload+1);
    if (payload[0]==FREQ) {
			freq = (*data) * 100;
			//SendFreq(*data);
		}
    if (payload[0]==AMP){
      ConvertAmplitude(data);
      }
    if (payload[0]==VOUT) Vout = *data;
		if (payload[0]==SWEEP) sweep = 1 - sweep;
		if (payload[0]==FAST_SWEEP) fast_sweep = 1 - fast_sweep;
		
}



#endif
