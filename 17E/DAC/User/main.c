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

#define ADC_DMA_BUF_SIZE        100      /* ADC DMA�ɼ� BUF��С, Ӧ����ADCͨ������������ */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;               /* DMA����״̬��־, 0,δ���; 1, ����� */
//-----------------------------------------------------------------
// ������
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
		dac_init(1);                /* ��ʼ��DAC1_OUT1ͨ�� */
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
