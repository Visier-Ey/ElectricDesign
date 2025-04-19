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
// ������
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
	
	
	sys_stm32_clock_init(9);    /* ����ʱ��, 72Mhz */
    delay_init(72);             /* ��ʱ��ʼ�� */
    usart_init(72, 115200);     /* ���ڳ�ʼ��Ϊ115200 */
	Delay_5ms(100);	
	
    AD9833_Init();
	// RDA5820 ��ʼ��
	RDA5820_WR_Reg(0X53,650);
  RDA5820_WR_Reg(0X54,1150);
	RDA5820_Band_Set(3);	//����Ƶ��Ϊ�Զ���
	RDA5820_Space_Set(0);	//���ò���Ϊ50Khz
	RDA5820_TxPGA_Set(3);	//�ź���������Ϊ3
	RDA5820_TxPAG_Set(63);	//���书��Ϊ���.
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
