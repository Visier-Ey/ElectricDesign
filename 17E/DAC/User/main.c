//-----------------------------------------------------------------
// 程序描述:
// 　　stm32_AD9854测试程序_V1.1
// 作　　者: 凌智电子
// 开始日期: 2015-07-15
// 完成日期: 2015-07-16
// 修改日期: 2015-07-16
// 当前版本: V1.1
// 历史版本:
// 　- V1.0: 基本的AD9854并行控制输出，液晶显示功能
// 　- V1.1：并行控制转串行控制
// 调试工具: 1602液晶屏、LZE_ST_LINK2
// 说　　明: 
//				(1) 调试使用的系统时钟频率Fsysclk=72MHz;
//     		(2) AD9854的数据传输方式:串行传输方式;
//				(3) AD9854_IO与核心板连接方式如下
//-----------------------------------------------------------------
//               IO 连接说明
//-----------------------------------------------------------------
//    AD9854         |      STM32
// PIV							 -->	 +5V
// GND							 -->	 GND
// A0/SDIO           -->   GPIOA_PIN5				
// A1/SDO            -->   GPIOA_PIN6			
// A2/IORST          -->   GPIOA_PIN7
// RD                -->   GPIOF_PIN0
// WR                -->   GPIOF_PIN1
// UDCLK             -->   GPIOF_PIN2
// RESET             -->   GPIOF_PIN3
// S/P               -->   GPIOF_PIN4
//-----------------------------------------------------------------
//				(4) 由于AD9854功耗高, 请保证AD9854模块的供电功率, 供电电源建议5V1A电源
//        (5) 本测试程序实现基本的AD9854控制输出，即1MHz正弦波输出。可通过修改代码(Fre值)修改输出频率
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "./BSP/USER/Delay.h"
#include "./BSP/USER/AD9854.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/RDA5820/rda5820.h"
#include "./BSP/DMA/dma.h"
#include "./BSP/LED/led.h"
#include "launchStation.h"
#include "./BSP/DAC/dac.h"
#include "AnalysisCmd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/PE4302/pe4302.h"

#define ADC_DMA_BUF_SIZE        100      /* ADC DMA采集 BUF大小, 应等于ADC通道数的整数倍 */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0,未完成; 1, 已完成 */
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------

void setDAC(uint16_t dacx){
//	 DAC1->DHR12R1 = dacx;
}


int main(void) {           // 7???? (0~127)
    int gain = 2047;       // ???? (???)
		int Vout = 100;
		uint32_t freq = 100;
		int att = 0;
		uint16_t mv200 = 1800;
    uint16_t dacval = 0;
    // ?????
    sys_stm32_clock_init(9);    // ???????
    delay_init(72);             // ?????
    usart_init(72, 115200);     // ?????
    Delay_5ms(100);
    GPIO_AD9854_Configuration(); // AD9854 GPIO??
    Delay_1ms(5);
    AD9854_Init();              // AD9854???
    PE4302_Init();              // PE4302(???)???
    Delay_1ms(15);
    led_init();                 // LED???
    key_init();                 // ?????
		dac_init(1);                /* 初始化DAC1_OUT1通道 */
    // ?????????
    AD9854_SetSine(freq * 10000, mv200);
	  PE4302_Set_Attenuation(0); // Set attenuation to i dB
		calc_Vol(freq,Vout,&gain,&att);
		AD9854_SetSine(freq * 10000, gain);
		PE4302_Set_Attenuation(att); // Set attenuation to i dB
    printf("Program Start\n");

    while (1) {
//        for (Vout = 5; Vout <= 100; Vout++) {
//						calc_Vol(freq,Vout,&gain,&att);
//						AD9854_SetSine(freq * 10000, gain);
//					  PE4302_Set_Attenuation(att); // Set attenuation to i dB
//						printf("Vout: %d, gain: %d, att: %d\n",Vout,gain,att);
//						delay_ms(50);             
//						LED0_TOGGLE();            
//        }

//       for (Vout = 100; Vout >= 5; Vout--) {
//						calc_Vol(freq,Vout,&gain,&att);
//						AD9854_SetSine(freq * 10000, gain);
//					  PE4302_Set_Attenuation(att); // Set attenuation to i dB
//						printf("Vout: %d, gain: %d, att: %d\n",Vout,gain,att);
//            delay_ms(50);
//            LED0_TOGGLE();
//        }
				for (freq = 100; freq <= 4000; freq+=100) {
						calc_Vol(freq,Vout,&gain,&att);
						AD9854_SetSine(freq * 10000, gain);
					  PE4302_Set_Attenuation(att); // Set attenuation to i dB
						printf("Vout: %d, gain: %d, att: %d\n",Vout,gain,att);
						delay_ms(50);             
						LED0_TOGGLE();            
        }

       for (freq = 4000; freq >= 100; freq-=100) {
						calc_Vol(freq,Vout,&gain,&att);
						AD9854_SetSine(freq * 10000, gain);
					  PE4302_Set_Attenuation(att); // Set attenuation to i dB
						printf("Vout: %d, gain: %d, att: %d\n",Vout,gain,att);
            delay_ms(50);
            LED0_TOGGLE();
        }
    }
}
// set the callback function
void USART_RxCompleteCallback(void){
}


//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
