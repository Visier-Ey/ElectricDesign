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
#define Kf(Kf) printf("x3.val=%d",Kf);End()


void End(){
    putchar(0xff); 
    putchar(0xff); 
    putchar(0xff); 
    // putchar(0x0a);
}

float calculateAMModulate(float var, uint8_t CarrierFreq) {
  float y = 0;
   if (CarrierFreq >= 20) {
    y = 9.301427f * pow(var, 0) + -308.176376f * pow(var, 1) + 4039.717532f * pow(var, 2) + -26501.013301f * pow(var, 3) + 93304.042976f * pow(var, 4) + -168315.20379f * pow(var, 5) + 122254.461479f * pow(var, 6);
  } else if (CarrierFreq >= 19) {
    y = -3.320345f * pow(var, 0) + 101.822451f * pow(var, 1) + -1176.763585f * pow(var, 2) + 7065.253655f * pow(var, 3) + -22787.285224f * pow(var, 4) + 37591.509089f * pow(var, 5) + -24839.063207f * pow(var, 6);
  } else if (CarrierFreq >= 18) {
    y = 8.792781f * pow(var, 0) + -282.759749f * pow(var, 1) + 3596.250614f * pow(var, 2) + -22855.395361f * pow(var, 3) + 77879.964893f * pow(var, 4) + -135847.044576f * pow(var, 5) + 95324.463224f * pow(var, 6);
  } else if (CarrierFreq >= 17) {
    y = -3.346102f * pow(var, 0) + 101.980939f * pow(var, 1) + -1176.36442f * pow(var, 2) + 7047.066946f * pow(var, 3) + -22663.498433f * pow(var, 4) + 37243.837813f * pow(var, 5) + -24503.508623f * pow(var, 6);
  } else if (CarrierFreq >= 16) {
    y = -3.008409f * pow(var, 0) + 88.632867f * pow(var, 1) + -980.810058f * pow(var, 2) + 5655.154383f * pow(var, 3) + -17513.016706f * pow(var, 4) + 27716.387565f * pow(var, 5) + -17550.545824f * pow(var, 6);
  } else if (CarrierFreq >= 15) {
    y = -0.060197f * pow(var, 0) + 0.279033f * pow(var, 1) + 35.875356f * pow(var, 2) + -191.813155f * pow(var, 3) + 423.39103f * pow(var, 4) + -366.822358f * pow(var, 5) + 99.29789f * pow(var, 6);
  } else if (CarrierFreq >= 14) {
    y = 4.089715f * pow(var, 0) + -127.126002f * pow(var, 1) + 1569.663571f * pow(var, 2) + -9520.404993f * pow(var, 3) + 30802.186875f * pow(var, 4) + -50846.405468f * pow(var, 5) + 33695.568856f * pow(var, 6);
  } else if (CarrierFreq >= 13) {
    y = 3.022237f * pow(var, 0) + -92.265093f * pow(var, 1) + 1123.191539f * pow(var, 2) + -6657.270526f * pow(var, 3) + 21038.650836f * pow(var, 4) + -33941.110038f * pow(var, 5) + 22006.588135f * pow(var, 6);
  } else if (CarrierFreq >= 12) {
    y = -2.232815f * pow(var, 0) + 60.700642f * pow(var, 1) + -606.600882f * pow(var, 2) + 3184.893242f * pow(var, 3) + -8959.532032f * pow(var, 4) + 12835.542613f 
* pow(var, 5) + -7319.909982f * pow(var, 6);
  } else if (CarrierFreq >= 11) {
    y = -3.130699f * pow(var, 0) + 85.620407f * pow(var, 1) + -878.186563f * pow(var, 2) + 4680.071726f * pow(var, 3) + -13389.180022f * pow(var, 4) + 19583.500802f * pow(var, 5) + -11477.292054f * pow(var, 6);
  } else if (CarrierFreq >= 10) {
    y = -1.369339f * pow(var, 0) + 39.372633f * pow(var, 1) + -395.438146f * pow(var, 2) + 2101.772381f * pow(var, 3) + -5933.912975f * pow(var, 4) + 8475.433518f * pow(var, 5) + -4792.839595f * pow(var, 6);
  } else if (CarrierFreq >= 7) {
    y = -2.618309f * pow(var, 0) + 64.987968f * pow(var, 1) + -595.494344f * pow(var, 2) + 2850.912448f * pow(var, 3) + -7297.861446f * pow(var, 4) + 9471.455161f * pow(var, 5) + -4853.243599f * pow(var, 6);
  } else if (CarrierFreq >= 4) {
    y = -1.993225f * pow(var, 0) + 45.790991f * pow(var, 1) + -361.608469f * pow(var, 2) + 1404.691632f * pow(var, 3) + -2524.88111f * pow(var, 4) + 1472.294393f * 
pow(var, 5) + 488.81051f * pow(var, 6);
  } else if (CarrierFreq >= 1) {
    y = 0.383388f * pow(var, 0) + -14.067779f * pow(var, 1) + 229.381612f * pow(var, 2) + -1557.508197f * pow(var, 3) + 5463.946025f * pow(var, 4) + -9571.688094f * pow(var, 5) + 6632.155121f * pow(var, 6);
  } else {
    y = 0.383388f * pow(var, 0) + -14.067779f * pow(var, 1) + 229.381612f * pow(var, 2) + -1557.508197f * pow(var, 3) + 5463.946025f * pow(var, 4) + -9571.688094f * pow(var, 5) + 6632.155121f * pow(var, 6);
  }
  if (y<=0) y = 0.1f;
  return y;
}

float calculateFMModulate(float var, uint16_t ModFreq) {
  float y = 0;
  // var /= 2;
  if (ModFreq >= 10000) {
    y = -0.060619f * pow(var, 0) + 0.003588f * pow(var, 1);
  } else if (ModFreq >= 9800) {
    y = -0.05318f * pow(var, 0) + 0.003549f * pow(var, 1);
  } else if (ModFreq >= 9600) {
    y = -0.057064f * pow(var, 0) + 0.003547f * pow(var, 1);
  } else if (ModFreq >= 9400) {
    y = -0.052955f * pow(var, 0) + 0.003531f * pow(var, 1);
  } else if (ModFreq >= 9200) {
    y = -0.051596f * pow(var, 0) + 0.003512f * pow(var, 1);
  } else if (ModFreq >= 9000) {
    y = -0.057955f * pow(var, 0) + 0.003494f * pow(var, 1);
  } else if (ModFreq >= 8800) {
    y = -0.047646f * pow(var, 0) + 0.003453f * pow(var, 1);
  } else if (ModFreq >= 8600) {
    y = -0.054092f * pow(var, 0) + 0.003425f * pow(var, 1);
  } else if (ModFreq >= 8400) {
    y = -0.055659f * pow(var, 0) + 0.003397f * pow(var, 1);
  } else if (ModFreq >= 8200) {
    y = -0.043938f * pow(var, 0) + 0.003357f * pow(var, 1);
  } else if (ModFreq >= 8000) {
    y = -0.054947f * pow(var, 0) + 0.003351f * pow(var, 1);
  } else if (ModFreq >= 7800) {
    y = -0.051011f * pow(var, 0) + 0.003334f * pow(var, 1);
  } else if (ModFreq >= 7600) {
    y = -0.04654f * pow(var, 0) + 0.003324f * pow(var, 1);
  } else if (ModFreq >= 7400) {
    y = -0.04596f * pow(var, 0) + 0.003331f * pow(var, 1);
  } else if (ModFreq >= 7200) {
    y = -0.048529f * pow(var, 0) + 0.003348f * pow(var, 1);
  } else if (ModFreq >= 7000) {
    y = -0.044748f * pow(var, 0) + 0.003366f * pow(var, 1);
  } else if (ModFreq >= 6800) {
    y = -0.048484f * pow(var, 0) + 0.003391f * pow(var, 1);
  } else if (ModFreq >= 6600) {
    y = -0.049242f * pow(var, 0) + 0.00342f * pow(var, 1);
  } else if (ModFreq >= 6400) {
    y = -0.053528f * pow(var, 0) + 0.003454f * pow(var, 1);
  } else if (ModFreq >= 6200) {
    y = -0.052446f * pow(var, 0) + 0.003473f * pow(var, 1);
  } else if (ModFreq >= 6000) {
    y = -0.054541f * pow(var, 0) + 0.003496f * pow(var, 1);
  } else if (ModFreq >= 5800) {
    y = -0.054313f * pow(var, 0) + 0.003505f * pow(var, 1);
  } else if (ModFreq >= 5600) {
    y = -0.055095f * pow(var, 0) + 0.00351f * pow(var, 1);
  } else if (ModFreq >= 5400) {
    y = -0.05614f * pow(var, 0) + 0.003509f * pow(var, 1);
  } else if (ModFreq >= 5200) {
    y = -0.057037f * pow(var, 0) + 0.0035f * pow(var, 1);
  } else if (ModFreq >= 5000) {
    y = -0.052393f * pow(var, 0) + 0.003494f * pow(var, 1);
  } else if (ModFreq >= 4800) {
    y = -0.052901f * pow(var, 0) + 0.003482f * pow(var, 1);
  } else if (ModFreq >= 4600) {
    y = -0.057706f * pow(var, 0) + 0.003477f * pow(var, 1);
  } else if (ModFreq >= 4400) {
    y = -0.052512f * pow(var, 0) + 0.003478f * pow(var, 1);
  } else if (ModFreq >= 4200) {
    y = -0.060042f * pow(var, 0) + 0.003492f * pow(var, 1);
  } else if (ModFreq >= 4000) {
    y = -0.054769f * pow(var, 0) + 0.003511f * pow(var, 1);
  } else if (ModFreq >= 3800) {
    y = -0.056044f * pow(var, 0) + 0.003549f * pow(var, 1);
  } else if (ModFreq >= 3600) {
    y = -0.066021f * pow(var, 0) + 0.003609f * pow(var, 1);
  } else if (ModFreq >= 3400) {
    y = -0.066261f * pow(var, 0) + 0.003682f * pow(var, 1);
  } else if (ModFreq >= 3200) {
    y = -0.065898f * pow(var, 0) + 0.003766f * pow(var, 1);
  } else if (ModFreq >= 3000) {
    y = -0.069989f * pow(var, 0) + 0.003868f * pow(var, 1);
  } else if (ModFreq >= 2800) {
    y = -0.068966f * pow(var, 0) + 0.003989f * pow(var, 1);
  } else if (ModFreq >= 2600) {
    y = -0.067963f * pow(var, 0) + 0.00412f * pow(var, 1);
  } else if (ModFreq >= 2400) {
    y = -0.079395f * pow(var, 0) + 0.004294f * pow(var, 1);
  } else if (ModFreq >= 2200) {
    y = -0.080467f * pow(var, 0) + 0.004476f * pow(var, 1);
  } else if (ModFreq >= 2000) {
    y = -0.084848f * pow(var, 0) + 0.004692f * pow(var, 1);
  } else if (ModFreq >= 1800) {
    y = -0.09497f * pow(var, 0) + 0.004955f * pow(var, 1);
  } else if (ModFreq >= 1600) {
    y = -0.111861f * pow(var, 0) + 0.005301f * pow(var, 1);
  } else if (ModFreq >= 1400) {
    y = -0.120252f * pow(var, 0) + 0.005719f * pow(var, 1);
  } else if (ModFreq >= 1200) {
    y = -0.127421f * pow(var, 0) + 0.006293f * pow(var, 1);
  } else if (ModFreq >= 1000) {
    y = -0.091212f * pow(var, 0) + 0.00711f * pow(var, 1);
  } else {
    y = -0.091212f * pow(var, 0) + 0.00711f * pow(var, 1);
  }
  return y;
}

float calculateFSKShift(float var, uint16_t CarrierFreq) {
  float y = 0;
  if (CarrierFreq >= 5000) {
    y = -0.571193f * pow(var, 0) + 0.005801f * pow(var, 1);
  } else if (CarrierFreq >= 4000) {
    y = -0.438888f * pow(var, 0) + 0.005684f * pow(var, 1);
  } else if (CarrierFreq >= 3000) {
    y = -0.169359f * pow(var, 0) + 0.005923f * pow(var, 1);
  } else if (CarrierFreq >= 2000) {
    y = -0.25069f * pow(var, 0) + 0.00769f * pow(var, 1);
  } else if (CarrierFreq >= 1000) {
    y = -1.179814f * pow(var, 0) + 0.015145f * pow(var, 1);
  } else {
    y = -1.179814f * pow(var, 0) + 0.015145f * pow(var, 1);
  }
  return y/2;
}

#define CW_TYPE 0
#define AM_TYPE 1
#define ASK_TYPE 2
#define FM_TYPE 3
#define FSK_TYPE 4

void printType(uint8_t type){
    switch (type)
    {
    case CW_TYPE:
      printf("CW\n");
      break;
    case AM_TYPE:
      printf("AM\n");
      break;
    case ASK_TYPE:
      printf("ASK\n");
      break;
    case FM_TYPE:
      printf("FM\n");
      break;
    case FSK_TYPE:
      printf("FSK\n");
      break;
    default:
      break;
    }
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