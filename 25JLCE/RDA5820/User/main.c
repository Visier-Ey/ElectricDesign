//-----------------------------------------------------------------
// ��������:
// ����stm32_AD9854���Գ���_V1.1
// ��������: ���ǵ���
// ��ʼ����: 2015-07-15
// �������: 2015-07-16
// �޸�����: 2015-07-16
// ��ǰ�汾: V1.1
// ��ʷ�汾:
// ��- V1.0: ������AD9854���п��������Һ����ʾ����
// ��- V1.1�����п���ת���п���
// ���Թ���: 1602Һ������LZE_ST_LINK2
// ˵������: 
//				(1) ����ʹ�õ�ϵͳʱ��Ƶ��Fsysclk=72MHz;
//     		(2) AD9854�����ݴ��䷽ʽ:���д��䷽ʽ;
//				(3) AD9854_IO����İ����ӷ�ʽ����
//-----------------------------------------------------------------
//               IO ����˵��
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
//				(4) ����AD9854���ĸ�, �뱣֤AD9854ģ��Ĺ��繦��, �����Դ����5V1A��Դ
//        (5) �����Գ���ʵ�ֻ�����AD9854�����������1MHz���Ҳ��������ͨ���޸Ĵ���(Freֵ)�޸����Ƶ��
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include <stm32f10x.h>
#include "Delay.h"
#include "AD9854.h"
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/RDA5820/rda5820.h"
#include "./BSP/RDA5820/rda5820_2.h"
#include "./BSP/DMA/dma.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/LED/led.h"
#include "launchStation.h"
#include "AnalysisCmd.h"

#define ADC_DMA_BUF_SIZE        100     
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;         
//-----------------------------------------------------------------

//-----------------------------------------------------------------
u16 getPeakFreq()
{
	u16 i = 0, temp = 0, rssi_peak=0, f_peak = 7500;
	for (i = 7600; i <= 9500; i+=100)
			{
				RDA5820_Freq_Set(i); 
				delay_ms(20);			  
				temp = RDA5820_Rssi_Get(); 
				delay_ms(1);
				if (temp>rssi_peak)
				{
					f_peak = i;
					rssi_peak = temp;
				}
			}
		return f_peak;
}

int main(void)
{
	uint32_t times=0;
	//TEST
	uint16_t f_peak=0;
	u8 currentRssi=0;
	
	sys_stm32_clock_init(9);   
	delay_init(72);         
	usart_init(72, 115200);   
	Delay_5ms(100);	
	while(RDA5820_Init());
	// while(RDA5820_Init_2());
	// * 5820 1
	RDA5820_WR_Reg(0X53,650);
	RDA5820_WR_Reg(0X54,1150);
	RDA5820_Band_Set(3);	
	RDA5820_Space_Set(0);	
	RDA5820_RX_Mode();
	RDA5820_Freq_Set(f_peak);
	// * 5820 2
	// RDA5820_WR_Reg_2(0X53,650);
	// RDA5820_WR_Reg_2(0X54,1150);
	// RDA5820_Band_Set_2(3);
	// RDA5820_Space_Set_2(0);
	// RDA5820_RX_Mode_2();
	// RDA5820_Freq_Set_2(f_peak);

	// * 5820_2 to search the highest frequency,and set it to 5820_1
	
	f_peak=7500;

	f_peak = getPeakFreq();
	RDA5820_Freq_Set(f_peak);
	printf("%c",(uint8_t)(f_peak/100)-75);
    while (1)
    {
			currentRssi=RDA5820_Rssi_Get();
			delay_ms(50);
			if (currentRssi<80)
			{
				f_peak = getPeakFreq();
				RDA5820_Freq_Set(f_peak);
				printf("%c",(uint8_t)(f_peak/100)-75);
				Delay_1ms(1000);
			}
	}	
		
}
// set the callback function
void USART_RxCompleteCallback(void){
//	uint8_t len = g_usart_rx_sta & 0x3fff;
//	if(AnalysisCmd(g_usart_rx_buf,len)==ANALY_OK) TACK();
//	else TNACK();
//	g_usart_rx_sta=0;
}


//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
