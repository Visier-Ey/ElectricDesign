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
#include "AD9854.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/RDA5820/rda5820.h"
#include "./BSP/DMA/dma.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/LED/led.h"
#include "launchStation.h"
#include "AnalysisCmd.h"

#define ADC_DMA_BUF_SIZE        100      /* ADC DMA采集 BUF大小, 应等于ADC通道数的整数倍 */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;               /* DMA传输状态标志, 0,未完成; 1, 已完成 */
//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
int main(void)
{
	uint16_t i;
    uint16_t adcx;
    uint32_t sum;
	uint16_t offset=300; // 单位kHz
	float control_amplitude=1; //单位V
	uint32_t base_freq=20000;
	uint32_t mix_freq = 25000; //单位kHz
	uint32_t freq=48500 + mix_freq;
    float temp;
	uint32_t times=0;
	
	
	sys_stm32_clock_init(9);    /* 设置时钟, 72Mhz */
    delay_init(72);             /* 延时初始化 */
    usart_init(72, 115200);     /* 串口初始化为115200 */
	Delay_5ms(100);	
	GPIO_AD9854_Configuration();
	Delay_1ms(5);
	AD9854_Init();
	Delay_1ms(15);
	AD9854_SetSine(mix_freq*1000,4095);//单位Hz
	while(RDA5820_Init());//等待初始化完成
	// RDA5820 初始化
	RDA5820_WR_Reg(0X53,650);
    RDA5820_WR_Reg(0X54,1150);
	RDA5820_Band_Set(3);	//设置频段为自定义
	RDA5820_Space_Set(0);	//设置步进为50Khz
	RDA5820_TxPGA_Set(3);	//信号增益设置为3
	RDA5820_TxPAG_Set(63);	//发射功率为最大.
	RDA5820_TX_Mode();
    
	RDA5820_Freq_Set(freq/10);
	printf("Programme Start\n");
    led_init();                 /* 初始化LED */
	adc_dma_init((uint32_t)&g_adc_dma_buf); /* 初始化ADC DMA采集 */
	
	adc_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动ADC DMA采集 */
	
    while (1)
    {
        if (g_adc_dma_sta == 1)
        {
            /* 计算DMA 采集到的ADC数据的平均值 */
            sum = 0;
			printf("adc_dma\n");
            for (i = 0; i < ADC_DMA_BUF_SIZE; i++)   /* 累加 */
            {
                sum += g_adc_dma_buf[i];
            }

            adcx = sum / ADC_DMA_BUF_SIZE;  /* 取平均值 */

            /* 显示结果 */

            temp = (float)adcx * (control_amplitude / 4096);              /* 获取计算后的带小数的实际电压值，比如3.1111 */
            
			mix_freq=(int)(normalize(temp,0,2*control_amplitude)*offset) + base_freq;
			// TODO : 设置混频频率
			AD9854_SetSine(mix_freq*1000,4095);
			
            g_adc_dma_sta = 0;                  /* 清除DMA采集完成状态标志 */
            adc_dma_enable(ADC_DMA_BUF_SIZE);   /* 启动下一次ADC DMA采集 */
        }
		times++;
		if (times % 100 ==0){
			printf("TOGGLE\n");
			LED0_TOGGLE();
		
		}
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
