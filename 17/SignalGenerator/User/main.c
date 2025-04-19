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
#include "./BSP/DMA/dma.h"
#include "./BSP/LED/led.h"
#include "launchStation.h"
#include "./BSP/DAC/dac.h"
#include "AnalysisCmd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/PE4302/pe4302.h"

#define ADC_DMA_BUF_SIZE        100      /* ADC DMA�ɼ� BUF��С, Ӧ����ADCͨ������������ */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;               /* DMA����״̬��־, 0,δ���; 1, ����� */
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
uint16_t freq = 2000;
uint16_t Vout = 50;
uint16_t dacval = 0;
uint16_t amp = 759;
uint8_t sweep = 0;
uint8_t fast_sweep = 0;
int main(void) {           // 7???? (0~127)
    int gain = 2047;       // ???? (???)
		int att;
		uint16_t mv200 = 1800;
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
    // ?????????
    AD9854_SetSine(freq * 10000, mv200);
	  PE4302_Set_Attenuation(0); // Set attenuation to i dB
		calc_Vol(freq,Vout,&gain,&att);
		AD9854_SetSine(freq * 10000, gain);
		PE4302_Set_Attenuation(att); // Set attenuation to i dB
		DAC_Config();
		DAC_SetChannel1Data(DAC_Align_12b_R, 4095);
    while (1) {
						calc_Vol(freq,Vout,&gain,&att);			
						AD9854_SetSine(freq * 10000, gain);
					  PE4302_Set_Attenuation(att); // Set attenuation to i dB
            DAC_SetChannel1Data(DAC_Align_12b_R, amp);
            delay_ms(100);

				for (;sweep != 0 && freq <= 4000; freq+=100) {
						calc_Vol(freq,Vout,&gain,&att);
						AD9854_SetSine(freq * 10000, gain);
					  PE4302_Set_Attenuation(att); // Set attenuation to i dB
            DAC_SetChannel1Data(DAC_Align_12b_R, amp);
						SendFreq(freq/100);
						delay_ms(50);             
						LED0_TOGGLE();            
        }

       for (;sweep != 0 && freq >= 100; freq-=100) {
						calc_Vol(freq,Vout,&gain,&att);
						AD9854_SetSine(freq * 10000, gain);
					  PE4302_Set_Attenuation(att); // Set attenuation to i dB
            DAC_SetChannel1Data(DAC_Align_12b_R, amp);
						SendFreq(freq/100);
            delay_ms(50);
            LED0_TOGGLE();
        }
			 if (fast_sweep != 0){
				 for (freq=0;fast_sweep != 0 && freq <= 4000; freq+=100) {
							calc_Vol(freq,Vout,&gain,&att);
							AD9854_SetSine(freq * 10000, gain);
							PE4302_Set_Attenuation(att); // Set attenuation to i dB
							DAC_SetChannel1Data(DAC_Align_12b_R, amp);
							SendFreq(freq/100);
							delay_ms(10);
							LED0_TOGGLE();
					}
				fast_sweep = 0;
			}
    }
}
// set the callback function
void USART_RxCompleteCallback(void){
	uint8_t len = g_usart_rx_sta & 0x3fff;
	AnalysisCmd(g_usart_rx_buf);
	g_usart_rx_sta=0;
}


//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
