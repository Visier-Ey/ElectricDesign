#include "main.h"
#include "AD9959.h"


#define system_clk 500000000	 //AD9959����Ƶ���趨Ϊ500MHz

#define uchar unsigned char
#define uint unsigned int

#define Delay(a) HAL_Delay(a)


//�ӳ���-----------------------------------------------------------

void GPIO_AD9959_Configuration(void)  //I/O�˿�����
{ 
// 	GPIO_InitTypeDef GPIO_InitStructure;

// 	// ʹ��IO��ʱ��
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_GPIOA, ENABLE);  
	
//   // ����C0-C2Ϊ����λ��C3Ϊ���ݴ���λ�����ౣ�ֵ͵�ƽ
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |	GPIO_Pin_2 | GPIO_Pin_3 |	GPIO_Pin_4 | GPIO_Pin_5
// 								|	GPIO_Pin_6 | GPIO_Pin_7; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		// �������
// 	GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
//   //��A4Ϊ��λλ������Ϊ�͵�ƽ
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9  |	GPIO_Pin_10 | GPIO_Pin_11	
// 								| GPIO_Pin_12;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	// �������
// 	GPIO_Init(GPIOA, &GPIO_InitStructure);
//! ALL Finished at GPIO_Init()
}



	void AD9959_Init(void)  //��ʼ��
{
	CS_1;
	SCLK_0;
	IO_update_0;
	PS0_0;
	PS1_0;
	PS2_0;
	PS3_0;
	
	SDIO0_0;
	SDIO1_0;
	SDIO2_0;
	SDIO3_0;
	
 	Reset_0;
 	Delay(6);
 	Reset_1;
 	Delay(100);
 	Reset_0;
}

//����Ƶ��ת����
void WrFrequencyTuningWorddata(double f,uchar *ChannelFrequencyTuningWorddata)
{
	unsigned char z;
	
	long int y;
	double x;					
	x=4294967296.0/system_clk;	//Ƶ�ʿ����ּ���
	f=f*x;                      
	y=(long int)f;				//ǿ��ת������
	
	z=(uchar)(y>>24);     //8λ����������ǿ��תΪ8λ�ַ���
	ChannelFrequencyTuningWorddata[0]=z;
	
	z=(uchar)(y>>16);
	ChannelFrequencyTuningWorddata[1]=z;
	
	z=(uchar)(y>>8);
	ChannelFrequencyTuningWorddata[2]=z;
	
	z=(uchar)(y>>0);
	ChannelFrequencyTuningWorddata[3]=z;
	
}

// ���ݸ��£�ͨ��ʹ��λ����ҪIO����
void IO_update(void)   
{
	IO_update_0;
	Delay(12);
	IO_update_1;
	Delay(24);
	IO_update_0;
}


//ͨ��
void WriteToAD9959ViaSpi(uchar RegisterAddress, uchar NumberofRegisters, uchar *RegisterData,uchar temp) 
{
	uchar	ControlValue = 0;
	uchar		ValueToWrite = 0;
	uchar	RegisterIndex = 0;
	uchar	i = 0;

	//��ControlValueΪһ��8λ����
	ControlValue = RegisterAddress;

	SCLK_0;
	CS_0;	 //bring CS low
	
	//д������
	for(i=0; i<8; i++)
	{
		SCLK_0;
		if(0x80 == (ControlValue & 0x80))
		{
			SDIO0_1;	  //Send one to SDIO0pin
		}
		else
		{
			SDIO0_0;	  //Send zero to SDIO0pin
		}
		SCLK_1;
		ControlValue <<= 1;	//Rotate data
	}
	SCLK_0;
	
	//д����
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++)
		{
			SCLK_0;
			if(0x80 == (ValueToWrite & 0x80))
			{
				SDIO0_1;	  //Send one to SDIO0pin
			}
			else
			{
				SDIO0_0;	  //Send zero to SDIO0pin
			}
			SCLK_1;
			ValueToWrite <<= 1;	//Rotate data
		}
		SCLK_0;		
	}	
	if(temp==1)
	  {
	  IO_update();
	  }	
  CS_1;	//bring CS high again
}

//������λת����
void WrPhaseOffsetTuningWorddata(double f,uchar *ChannelPhaseOffsetTuningWorddata)
{
	unsigned char z;
	
	long int y;
	double x;					
	x=16384.0/360;	//��λ�����ּ���
	f=f*x;                      
	y=(long int)f;				//ǿ��ת������
	
	z=(uchar)(y>>8);     //8λ����������ǿ��תΪ8λ�ַ���
	ChannelPhaseOffsetTuningWorddata[0]=z;
	
	z=(uchar)(y>>0);
	ChannelPhaseOffsetTuningWorddata[1]=z;
	
// 	ChannelPhaseOffsetTuningWorddata[2]=0x00;//�´��޸�ʱ����������Ȼ�����޸�����ı仯��ɨ��ʱ���ֲ���ɨ360��������������ʱ�������
// 	ChannelPhaseOffsetTuningWorddata[3]=0x00;//�����µ�
	
}

void WrAmplitudeTuningWorddata(double f,uchar *ChannelAmplitudeTuningWorddata) // ����ɨ��ʱ�����������½��ķ���
																																								//�������ע�������Ƶ������
{
	unsigned char z;
	
	unsigned long int y;
	double x;					
	x=1024.0/1024;	//���ȿ����ּ���
	f=f*x;                      
	y=(unsigned long int)f;				//ǿ��ת������
	
	z=(uchar)(y>>2);     //8λ����������ǿ��תΪ8λ�ַ���
	ChannelAmplitudeTuningWorddata[0]= z ;
	z=(uchar)(y<<6);		// ȡ��2λ
	ChannelAmplitudeTuningWorddata[1] = (z & 0xC0);
	ChannelAmplitudeTuningWorddata[2] = 0x00;
	ChannelAmplitudeTuningWorddata[3] = 0x00;

/* 
	z=(uchar)(y>>8);
	ChannelAmplitudeTuningWorddata[2]=z;
	
	z=(uchar)(y>>0);
	ChannelAmplitudeTuningWorddata[3]=z;
 */
}


void WrAmplitudeTuningWorddata1(double f,uchar *ChannelAmplitudeTuningWorddata,uchar *ASRAmplituteWordata) // ����������ȵĴ�С
																																								//�������ע�������Ƶ������
{ 
	unsigned char z;
	
	unsigned long int y;
	double x;					
	x=1024.0/1024;	//���ȿ����ּ���
	f=f*x*2.1;                      
	y=(unsigned long int)f;				//ǿ��ת������
	
	ASRAmplituteWordata[0] = ChannelAmplitudeTuningWorddata[0] ;
// 	ASRAmplituteWordata[1] = ChannelAmplitudeTuningWorddata[1] ;
// 	ASRAmplituteWordata[2] = ChannelAmplitudeTuningWorddata[2] ;
	
	
	z=(uchar)(y>>8);     //8λ����������ǿ��תΪ8λ�ַ���
	ChannelAmplitudeTuningWorddata[1] = (ChannelAmplitudeTuningWorddata[1] & 0xfc );
	ASRAmplituteWordata[1] = (ChannelAmplitudeTuningWorddata[1] | z );
	z=(uchar)(y<<0);		
	ASRAmplituteWordata[2] = z;
	

}







