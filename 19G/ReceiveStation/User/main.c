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
#include <stm32f10x.h>
#include "Delay.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/RDA5820/rda5820.h"
#include "./BSP/DMA/dma.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/AD9833/AD9833.h"
#include "launchStation.h"
#include "AnalysisCmd.h"


//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
int main(void)
{
	uint32_t base_freq=20000;
	uint32_t freq=48500;
	uint32_t mix_freq = 100000;
	uint8_t dir = 1;
	uint8_t step=100;
	uint8_t RSSI = 0;
	uint8_t OLD_RSSI = 0;
	uint16_t max_offset = 300;
	uint32_t times = 0;
	uint8_t minimal_step =5;
	
	
	sys_stm32_clock_init(9);    /* 设置时钟, 72Mhz */
    delay_init(72);             /* 延时初始化 */
    usart_init(72, 115200);     /* 串口初始化为115200 */
	Delay_5ms(100);	
	
    AD9833_Init();
	// RDA5820 初始化
	RDA5820_WR_Reg(0X53,650);
  RDA5820_WR_Reg(0X54,1150);
	RDA5820_Band_Set(3);	//设置频段为自定义
	RDA5820_Space_Set(0);	//设置步进为50Khz
	RDA5820_TxPGA_Set(3);	//信号增益设置为3
	RDA5820_TxPAG_Set(63);	//发射功率为最大.
	RDA5820_RX_Mode();
	RDA5820_Freq_Set(freq);
	printf("Programme Start\n");
  AD9833_WaveSeting(mix_freq,0,SIN_WAVE,0);
    while (1)
    {
		times++;
		// mix_freq step
		mix_freq += dir * step;
		// set mix freqency
		
		// AD9833_WaveSeting(mix_freq,0,SIN_WAVE,0);
		delay_us(10); // may wait for stable rssi
		// get rssi
		RSSI = RDA5820_Rssi_Get();
		// compare ... and change direction ...
		if (RSSI < OLD_RSSI) dir = -dir;
		OLD_RSSI = RSSI;
		if (mix_freq < base_freq - max_offset) dir = 1;
		if (mix_freq > base_freq + max_offset) dir = -1;
		// decay the step
		if(step > minimal_step && times%500==0) step-=5;
    }
}
// set the callback function
void USART_RxCompleteCallback(void){
	uint8_t len = g_usart_rx_sta & 0x3fff;
	if(AnalysisCmd(g_usart_rx_buf,len)==ANALY_OK) TACK();
	else TNACK();
	g_usart_rx_sta=0;
}


//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
