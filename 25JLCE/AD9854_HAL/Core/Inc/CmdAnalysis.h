#ifndef __CMD_ANALYSIS
#define __CMD_ANALYSIS
#include "stdio.h"
#include <stdint.h>
#include <stddef.h>

#define AM() printf("t1.txt=\"AM\"");End()
#define FM() printf("t1.txt=\"FM\"");End()
#define CW() printf("t1.txt=\"CW\"");End()
#define ASK() printf("t1.txt=\"ASK\"");End()
#define FSK() printf("t1.txt=\"FSK\"");End()
#define PSK() printf("t1.txt=\"PSK\"");End()
#define Modulation(mod) printf("x1.val=%d",mod);End()
#define ModFreq(freq) printf("x0.val=%d",freq);End()
#define OffsetFreq(freq) printf("x2.val=%d",freq);End()
#define Rc(Rc) printf("x4.val=%d",Rc);End()
#define Kf(Kf) printf("x3.val=%d",freq);End()


void End(){
    putchar(0xff); 
    putchar(0xff); 
    putchar(0xff); 
    // putchar(0x0a);
}

float calculateAMModulate(float var,uint8_t CarrierFreq)
{
  float y = 0;
  if (CarrierFreq > 19){
    y = -1994.6* pow(var, 6)  + 2620.7* pow(var, 5)  - 1212.5* pow(var, 4)  + 240.43* pow(var, 3)  - 18.026* pow(var, 2)  + 2.6729 * var - 0.0332;
  } else if (CarrierFreq > 17){
    y = 1470.6* pow(var, 6)  - 1637.1* pow(var, 5)  + 760.78* pow(var, 4)  - 185.28* pow(var, 3)  + 24.292* pow(var, 2) + 0.9197 * var - 0.0112; 
  } else if (CarrierFreq > 15){
    y = 9672.8* pow(var, 6) - 13316* pow(var, 5) + 7238.6* pow(var, 4) - 1957.8* pow(var, 3) + 272.7* pow(var, 2) - 15.768* var + 0.4039;
  } else if (CarrierFreq > 13){
    y = 1847.9 * pow(var, 6) - 2732.2 * pow(var, 5) + 1609.3 * pow(var, 4) - 468.5 * pow(var, 3) + 68.616 * pow(var, 2) - 2.2219 * var + 0.0687;
  } else if (CarrierFreq > 11){
    y = 5199.7* pow(var, 6) - 6898.9* pow(var, 5) + 3558.4* pow(var, 4) - 896.44* pow(var, 3) + 113.95* pow(var, 2) - 4.5469* var + 0.116;
  } else if (CarrierFreq > 8){
    y = -1681.6* pow(var, 6) + 2924.7* pow(var, 5) - 1961.7* pow(var, 4) + 647.67* pow(var, 3) - 109.73* pow(var, 2) + 11.029* var - 0.2836;
  } else if (CarrierFreq > 4){
    y = 8869.8* pow(var, 6) - 12821* pow(var, 5) + 7328.2* pow(var, 4) - 2103.3* pow(var, 3) + 317* pow(var, 2) - 21.395* var + 0.6113;
  } else {
    y = 9551.3* pow(var, 6) - 14161* pow(var, 5) + 8363.2* pow(var, 4) - 2493.7* pow(var, 3) + 390.54* pow(var, 2) - 27.801* var + 0.8099;
  }
  y = y >= 1.0f ? 1.0f : y;
  return y;
}


float calculateFMModulate(float var, uint16_t CarrierFreq) {
  float y = 0;
  // var /= 2;
  if (CarrierFreq >= 10000) {
    y = -0.060619f * pow(var, 0) + 0.003588f * pow(var, 1);
  } else if (CarrierFreq >= 9800) {
    y = -0.05318f * pow(var, 0) + 0.003549f * pow(var, 1);
  } else if (CarrierFreq >= 9600) {
    y = -0.057064f * pow(var, 0) + 0.003547f * pow(var, 1);
  } else if (CarrierFreq >= 9400) {
    y = -0.052955f * pow(var, 0) + 0.003531f * pow(var, 1);
  } else if (CarrierFreq >= 9200) {
    y = -0.051596f * pow(var, 0) + 0.003512f * pow(var, 1);
  } else if (CarrierFreq >= 9000) {
    y = -0.057955f * pow(var, 0) + 0.003494f * pow(var, 1);
  } else if (CarrierFreq >= 8800) {
    y = -0.047646f * pow(var, 0) + 0.003453f * pow(var, 1);
  } else if (CarrierFreq >= 8600) {
    y = -0.054092f * pow(var, 0) + 0.003425f * pow(var, 1);
  } else if (CarrierFreq >= 8400) {
    y = -0.055659f * pow(var, 0) + 0.003397f * pow(var, 1);
  } else if (CarrierFreq >= 8200) {
    y = -0.043938f * pow(var, 0) + 0.003357f * pow(var, 1);
  } else if (CarrierFreq >= 8000) {
    y = -0.054947f * pow(var, 0) + 0.003351f * pow(var, 1);
  } else if (CarrierFreq >= 7800) {
    y = -0.051011f * pow(var, 0) + 0.003334f * pow(var, 1);
  } else if (CarrierFreq >= 7600) {
    y = -0.04654f * pow(var, 0) + 0.003324f * pow(var, 1);
  } else if (CarrierFreq >= 7400) {
    y = -0.04596f * pow(var, 0) + 0.003331f * pow(var, 1);
  } else if (CarrierFreq >= 7200) {
    y = -0.048529f * pow(var, 0) + 0.003348f * pow(var, 1);
  } else if (CarrierFreq >= 7000) {
    y = -0.044748f * pow(var, 0) + 0.003366f * pow(var, 1);
  } else if (CarrierFreq >= 6800) {
    y = -0.048484f * pow(var, 0) + 0.003391f * pow(var, 1);
  } else if (CarrierFreq >= 6600) {
    y = -0.049242f * pow(var, 0) + 0.00342f * pow(var, 1);
  } else if (CarrierFreq >= 6400) {
    y = -0.053528f * pow(var, 0) + 0.003454f * pow(var, 1);
  } else if (CarrierFreq >= 6200) {
    y = -0.052446f * pow(var, 0) + 0.003473f * pow(var, 1);
  } else if (CarrierFreq >= 6000) {
    y = -0.054541f * pow(var, 0) + 0.003496f * pow(var, 1);
  } else if (CarrierFreq >= 5800) {
    y = -0.054313f * pow(var, 0) + 0.003505f * pow(var, 1);
  } else if (CarrierFreq >= 5600) {
    y = -0.055095f * pow(var, 0) + 0.00351f * pow(var, 1);
  } else if (CarrierFreq >= 5400) {
    y = -0.05614f * pow(var, 0) + 0.003509f * pow(var, 1);
  } else if (CarrierFreq >= 5200) {
    y = -0.057037f * pow(var, 0) + 0.0035f * pow(var, 1);
  } else if (CarrierFreq >= 5000) {
    y = -0.052393f * pow(var, 0) + 0.003494f * pow(var, 1);
  } else if (CarrierFreq >= 4800) {
    y = -0.052901f * pow(var, 0) + 0.003482f * pow(var, 1);
  } else if (CarrierFreq >= 4600) {
    y = -0.057706f * pow(var, 0) + 0.003477f * pow(var, 1);
  } else if (CarrierFreq >= 4400) {
    y = -0.052512f * pow(var, 0) + 0.003478f * pow(var, 1);
  } else if (CarrierFreq >= 4200) {
    y = -0.060042f * pow(var, 0) + 0.003492f * pow(var, 1);
  } else if (CarrierFreq >= 4000) {
    y = -0.054769f * pow(var, 0) + 0.003511f * pow(var, 1);
  } else if (CarrierFreq >= 3800) {
    y = -0.056044f * pow(var, 0) + 0.003549f * pow(var, 1);
  } else if (CarrierFreq >= 3600) {
    y = -0.066021f * pow(var, 0) + 0.003609f * pow(var, 1);
  } else if (CarrierFreq >= 3400) {
    y = -0.066261f * pow(var, 0) + 0.003682f * pow(var, 1);
  } else if (CarrierFreq >= 3200) {
    y = -0.065898f * pow(var, 0) + 0.003766f * pow(var, 1);
  } else if (CarrierFreq >= 3000) {
    y = -0.069989f * pow(var, 0) + 0.003868f * pow(var, 1);
  } else if (CarrierFreq >= 2800) {
    y = -0.068966f * pow(var, 0) + 0.003989f * pow(var, 1);
  } else if (CarrierFreq >= 2600) {
    y = -0.067963f * pow(var, 0) + 0.00412f * pow(var, 1);
  } else if (CarrierFreq >= 2400) {
    y = -0.079395f * pow(var, 0) + 0.004294f * pow(var, 1);
  } else if (CarrierFreq >= 2200) {
    y = -0.080467f * pow(var, 0) + 0.004476f * pow(var, 1);
  } else if (CarrierFreq >= 2000) {
    y = -0.084848f * pow(var, 0) + 0.004692f * pow(var, 1);
  } else if (CarrierFreq >= 1800) {
    y = -0.09497f * pow(var, 0) + 0.004955f * pow(var, 1);
  } else if (CarrierFreq >= 1600) {
    y = -0.111861f * pow(var, 0) + 0.005301f * pow(var, 1);
  } else if (CarrierFreq >= 1400) {
    y = -0.120252f * pow(var, 0) + 0.005719f * pow(var, 1);
  } else if (CarrierFreq >= 1200) {
    y = -0.127421f * pow(var, 0) + 0.006293f * pow(var, 1);
  } else if (CarrierFreq >= 1000) {
    y = -0.091212f * pow(var, 0) + 0.00711f * pow(var, 1);
  } else {
    y = -0.091212f * pow(var, 0) + 0.00711f * pow(var, 1);
  }
  return y;
}

#define AM_TYPE 1
#define ASK_TYPE 2
#define FM_TYPE 3
#define FSK_TYPE 4

void printType(uint8_t type){
    // switch (type)
    // {
    // case AM_TYPE:
    //   printf("AM\n");
    //   break;
    // case ASK_TYPE:
    //   printf("ASK\n");
    //   break;
    // case FM_TYPE:
    //   printf("FM\n");
    //   break;
    // case FSK_TYPE:
    //   printf("FSK\n");
    //   break;
    // default:
    //   break;
    // }
  }


  uint8_t JudgeType(uint8_t type){
    static uint8_t types[40] = {0};
    static uint8_t index = 0;
    uint8_t _type = 0;
    uint8_t AMCount = 0;
    uint8_t ASKCount = 0;
    uint8_t FMCount = 0;
    uint8_t FSKCount = 0;
    types[index] = type;
    index = (index + 1) % 40;
    for (int i = 0; i < 40; i++)
    {
      if (types[i] == AM_TYPE) AMCount++;
      else if (types[i] == ASK_TYPE) ASKCount++;
      else if (types[i] == FM_TYPE) FMCount++;
      else if (types[i] == FSK_TYPE) FSKCount++;
    }
    
    if (AMCount > ASKCount && AMCount > FMCount && AMCount > FSKCount) _type = AM_TYPE;
    else if (ASKCount > AMCount && ASKCount > FMCount && ASKCount > FSKCount) _type = ASK_TYPE;
    else if (FMCount > AMCount && FMCount > ASKCount && FMCount > FSKCount) _type = FM_TYPE;
    else if (FSKCount > AMCount && FSKCount > ASKCount && FSKCount > FMCount) _type = FSK_TYPE;
    
    return _type;
  }
  
  float sum(uint16_t *arr, int len) {
    float sum = 0;
    for (int i = 0; i < len; i++) {
      sum += arr[i];
    }
    return sum*1.f;
  }
  
#endif