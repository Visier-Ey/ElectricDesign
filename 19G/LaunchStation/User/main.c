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
#include "./BSP/ADC/adc.h"
#include "./BSP/LED/led.h"
#include "launchStation.h"
#include "AnalysisCmd.h"

#define ADC_DMA_BUF_SIZE        100      /* ADC DMA�ɼ� BUF��С, Ӧ����ADCͨ������������ */
uint16_t g_adc_dma_buf[ADC_DMA_BUF_SIZE];   /* ADC DMA BUF */

extern uint8_t g_adc_dma_sta;               /* DMA����״̬��־, 0,δ���; 1, ����� */
//-----------------------------------------------------------------
// ������
//-----------------------------------------------------------------
int main(void)
{
	uint16_t i;
    uint16_t adcx;
    uint32_t sum;
	uint16_t offset=300; // ��λkHz
	float control_amplitude=1; //��λV
	uint32_t base_freq=20000;
	uint32_t mix_freq = 25000; //��λkHz
	uint32_t freq=48500 + mix_freq;
    float temp;
	uint32_t times=0;
	
	
	sys_stm32_clock_init(9);    /* ����ʱ��, 72Mhz */
    delay_init(72);             /* ��ʱ��ʼ�� */
    usart_init(72, 115200);     /* ���ڳ�ʼ��Ϊ115200 */
	Delay_5ms(100);	
	GPIO_AD9854_Configuration();
	Delay_1ms(5);
	AD9854_Init();
	Delay_1ms(15);
	AD9854_SetSine(mix_freq*1000,4095);//��λHz
	while(RDA5820_Init());//�ȴ���ʼ�����
	// RDA5820 ��ʼ��
	RDA5820_WR_Reg(0X53,650);
    RDA5820_WR_Reg(0X54,1150);
	RDA5820_Band_Set(3);	//����Ƶ��Ϊ�Զ���
	RDA5820_Space_Set(0);	//���ò���Ϊ50Khz
	RDA5820_TxPGA_Set(3);	//�ź���������Ϊ3
	RDA5820_TxPAG_Set(63);	//���书��Ϊ���.
	RDA5820_TX_Mode();
    
	RDA5820_Freq_Set(freq/10);
	printf("Programme Start\n");
    led_init();                 /* ��ʼ��LED */
	adc_dma_init((uint32_t)&g_adc_dma_buf); /* ��ʼ��ADC DMA�ɼ� */
	
	adc_dma_enable(ADC_DMA_BUF_SIZE);   /* ����ADC DMA�ɼ� */
	
    while (1)
    {
        if (g_adc_dma_sta == 1)
        {
            /* ����DMA �ɼ�����ADC���ݵ�ƽ��ֵ */
            sum = 0;
			printf("adc_dma\n");
            for (i = 0; i < ADC_DMA_BUF_SIZE; i++)   /* �ۼ� */
            {
                sum += g_adc_dma_buf[i];
            }

            adcx = sum / ADC_DMA_BUF_SIZE;  /* ȡƽ��ֵ */

            /* ��ʾ��� */

            temp = (float)adcx * (control_amplitude / 4096);              /* ��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111 */
            
			mix_freq=(int)(normalize(temp,0,2*control_amplitude)*offset) + base_freq;
			// TODO : ���û�ƵƵ��
			AD9854_SetSine(mix_freq*1000,4095);
			
            g_adc_dma_sta = 0;                  /* ���DMA�ɼ����״̬��־ */
            adc_dma_enable(ADC_DMA_BUF_SIZE);   /* ������һ��ADC DMA�ɼ� */
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
