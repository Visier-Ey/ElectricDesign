#include "main.h"
#include "AD9854.h"

//**********************����Ϊϵͳʱ���Լ�����ر�������**************************/
/* 
  �˴������Լ�����Ҫ����ϵͳʱ���Լ�������ص����ӣ�һ������ֻ�迪��һ��   
  CLK_SetΪʱ�ӱ�Ƶ���ã�������4~20����Ƶ��������ܳ���300MHZ
  Freq_mult_ulong��Freq_mult_doulle��Ϊ2��48�η�����ϵͳʱ�ӣ�һ��Ϊ�����Σ�һ��Ϊ˫������
*/
//#define CLK_Set 7
//const u32  Freq_mult_ulong  = 1340357;
//const double Freq_mult_doulle = 1340357.032;

#define CLK_Set 9
const u32  Freq_mult_ulong  = 1042500;		 
const double Freq_mult_doulle = 1042499.9137431;

// #define CLK_Set 8
// const u32  Freq_mult_ulong  = 1172812;
// const double Freq_mult_doulle = 1172812.403;

//#define CLK_Set 10
//const u32  Freq_mult_ulong  = 938250;
//const double Freq_mult_doulle = 938249.9224;

u8 FreqWord[6];              //6���ֽ�Ƶ�ʿ�����

//====================================================================================
// ��ʼ��������
//====================================================================================
//====================================================================================
// void GPIO_AD9854_Configuration(void)
// ��������: AD9854�������ú���
// ��ڲ���: ��
// ���ز���: ��
// ȫ�ֱ���: ��
// ����ģ��: RCC_APB2PeriphClockCmd(); GPIO_Init();
// ע������: ��
//====================================================================================
//void GPIO_AD9854_Configuration(void)
//{ 
//	GPIO_InitTypeDef GPIO_InitStructure;

//	// ʹ��IO��ʱ��
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOF, ENABLE);   
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 |	GPIO_Pin_7 ; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;		// �������
//	GPIO_Init(GPIOA, &GPIO_InitStructure);

//	// ���ƶ˿�
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1  | GPIO_Pin_2  |	GPIO_Pin_3 | GPIO_Pin_4 
//								| GPIO_Pin_5 | GPIO_Pin_6 |	GPIO_Pin_0; 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;;		// �������
//	GPIO_Init(GPIOF, &GPIO_InitStructure);
//}

//====================================================================================
// AD9854������
//====================================================================================
//====================================================================================
//��������:void AD9854_WR_Byte(u8 Adata)
//��������:AD9854���п�д������
//��ڲ���:adata     ��ַ&����
													
//���ڲ���:��
//====================================================================================
void AD9854_WR_Byte(u8 Adata)
{
	unsigned char  i;
	
	for(i=8;i>0;i--)
	{
		if(Adata&0x80)						
			SPI_SDI_Set;
		else
			SPI_SDI_Clr;
		Adata <<= 1;	
		AD9854_WR_Clr;
		AD9854_WR_Set;
	}
}

//====================================================================================
//��������:void AD9854_Init(void)
//��������:AD9854��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_Init(void)
{
	AD9854_SP_Clr;								 // ���п���
	AD9854_WR_Clr;
	AD9854_UDCLK_Clr;
	AD9854_RST_Set;                // ��λAD9854
	HAL_Delay (1);
	AD9854_RST_Clr;
	SPI_IO_RST_Clr;
	AD9854_RD_Clr;
	
  AD9854_WR_Byte(CONTR);
// 	AD9854_WR_Byte(0x10);							//�رձȽ���
	AD9854_WR_Byte(0x00);							//�򿪱Ƚ���

	AD9854_WR_Byte(CLK_Set);					//����ϵͳʱ�ӱ�Ƶ       
	AD9854_WR_Byte(0x00);							//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x60);	

	AD9854_UDCLK_Set;              // ����AD9854���
	AD9854_UDCLK_Clr;	
}

//====================================================================================
//��������:void Freq_convert(long Freq)
//��������:�����ź�Ƶ������ת��
//��ڲ���:Freq   ��Ҫת����Ƶ�ʣ�ȡֵ��0~SYSCLK/2
//���ڲ���:��   ����Ӱ��ȫ�ֱ���FreqWord[6]��ֵ
//˵����   ���㷨λ���ֽ�����㷨���й�ʽFTW = (Desired Output Frequency �� 2N)/SYSCLK
//         �õ����㷨������N=48��Desired Output Frequency Ϊ����Ҫ��Ƶ�ʣ���Freq��SYSCLK
//         Ϊ�ɱ�̵�ϵͳʱ�ӣ�FTWΪ48Bit��Ƶ�ʿ����֣���FreqWord[6]
//====================================================================================
void Freq_convert(long Freq)   
{	
  u32 FreqBuf;
  u32 Temp=Freq_mult_ulong;   	       

	u8 Array_Freq[4];			     //������Ƶ�����ӷ�Ϊ�ĸ��ֽ�
	Array_Freq[0]=(u8) Freq;
	Array_Freq[1]=(u8)(Freq>>8);
	Array_Freq[2]=(u8)(Freq>>16);
	Array_Freq[3]=(u8)(Freq>>24);

	FreqBuf=Temp*Array_Freq[0];                  
	FreqWord[0]=FreqBuf;    
	FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[1]);
	FreqWord[1]=FreqBuf;
	FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[2]);
	FreqWord[2]=FreqBuf;
	FreqBuf>>=8;

	FreqBuf+=(Temp*Array_Freq[3]);
	FreqWord[3]=FreqBuf;
	FreqBuf>>=8;

	FreqWord[4]=FreqBuf;
	FreqWord[5]=FreqBuf>>8;	
}  

//====================================================================================
//��������:void AD9854_SetSine(ulong Freq,uint Shape)
//��������:AD9854���Ҳ���������
//��ڲ���:Freq   Ƶ�����ã�ȡֵ��ΧΪ0~(1/2)*SYSCLK
//         Shape  ��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095) ,ȡֵԽ��,����Խ�� 
//���ڲ���:��
//====================================================================================
void AD9854_SetSine(u32 Freq,u16 Shape)
{
	u8 count;
	u8 i=0;

	Freq_convert(Freq);		              //Ƶ��ת��

	for(count=6;count>0;)	              //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(i==0)
			AD9854_WR_Byte(FREQ1);
		AD9854_WR_Byte(FreqWord[--count]);
		i++;
  }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
	
	AD9854_WR_Byte(SHAPEI);						  //����Iͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_WR_Byte(SHAPEQ);							//����Qͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_UDCLK_Set;                   //����AD9854���
	AD9854_UDCLK_Clr;

}

//====================================================================================
//��������:void Freq_doublt_convert(double Freq)
//��������:�����ź�Ƶ������ת��
//��ڲ���:Freq   ��Ҫת����Ƶ�ʣ�ȡֵ��0~SYSCLK/2
//���ڲ���:��   ����Ӱ��ȫ�ֱ���FreqWord[6]��ֵ
//˵����   �й�ʽFTW = (Desired Output Frequency �� 2N)/SYSCLK�õ��ú�����
//         ����N=48��Desired Output Frequency Ϊ����Ҫ��Ƶ�ʣ���Freq��SYSCLK
//         Ϊ�ɱ�̵�ϵͳʱ�ӣ�FTWΪ48Bit��Ƶ�ʿ����֣���FreqWord[6]
//ע�⣺   �ú��������溯��������Ϊ�ú�������ڲ���Ϊdouble����ʹ�źŵ�Ƶ�ʸ���ȷ
//         ���꽨����100HZ�����ñ��������ڸ���100HZ��������ú���void Freq_convert(long Freq)
//====================================================================================
void Freq_double_convert(double Freq)   
{
	u32 Low32;
	u16 High16;
  double Temp=Freq_mult_doulle;   	            //23ca99Ϊ2��48�η�����120M
	Freq*=(double)(Temp);
//	1 0000 0000 0000 0000 0000 0000 0000 0000 = 4294967295
	High16 = (int)(Freq/4294967295);                  //2^32 = 4294967295
	Freq -= (double)High16*4294967295;
	Low32 = (u32)Freq;

	FreqWord[0]=Low32;	     
	FreqWord[1]=Low32>>8;
	FreqWord[2]=Low32>>16;
	FreqWord[3]=Low32>>24;
	FreqWord[4]=High16;
	FreqWord[5]=High16>>8;			
} 

//====================================================================================
//��������:void AD9854_SetSine_double(double Freq,uint Shape)
//��������:AD9854���Ҳ���������
//��ڲ���:Freq   Ƶ�����ã�ȡֵ��ΧΪ0~1/2*SYSCLK
//         Shape  ��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095) 
//���ڲ���:��
//====================================================================================
void AD9854_SetSine_double(double Freq,u16 Shape)
{
	u8 count=0;
	u8 i=0;

	Freq_double_convert(Freq);		           //Ƶ��ת��
	 
	for(count=6;count>0;)	                    //д��6�ֽڵ�Ƶ�ʿ�����  
  {
    if(i==0)
			AD9854_WR_Byte(FREQ1);
		AD9854_WR_Byte(FreqWord[--count]);
		i++;
  }
	
	AD9854_WR_Byte(SHAPEI);						  //����Iͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_WR_Byte(SHAPEQ);							//����Qͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));

	AD9854_UDCLK_Set;                    //����AD9854���
  AD9854_UDCLK_Clr;
}

//====================================================================================
//��������:void AD9854_InitFSK(void)
//��������:AD9854��FSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitFSK(void)
{
	AD9854_SP_Clr;
	AD9854_WR_Clr;                 // ������д���ƶ˿���Ϊ��Ч
	AD9854_UDCLK_Clr;
	AD9854_RST_Set;                // ��λAD9854
	HAL_Delay (1);
	AD9854_RST_Clr;
	SPI_IO_RST_Clr;
	AD9854_RD_Clr;

	AD9854_WR_Byte(CONTR);
	AD9854_WR_Byte(0x10);							//�رձȽ���
	AD9854_WR_Byte(CLK_Set);					//����ϵͳʱ�ӱ�Ƶ       
	AD9854_WR_Byte(0x02);							//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x60);      //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����

	AD9854_UDCLK_Set;                  //����AD9854���
  AD9854_UDCLK_Clr;
}

//====================================================================================
//��������:void AD9854_SetFSK(ulong Freq1,ulong Freq2)
//��������:AD9854��FSK����
//��ڲ���:Freq1   FSKƵ��1   
//         Freq2   FSKƵ��2
//���ڲ���:��
//====================================================================================
void AD9854_SetFSK(u32 Freq1,u32 Freq2)
{
  u8 count=6;
	u8 i=0,j=0;

	const u16 Shape=4000;	      //��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095)
	
	Freq_convert(Freq1);               //Ƶ��ת��1
	
	for(count=6;count>0;)	          //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(i==0)
			AD9854_WR_Byte(FREQ1);
		AD9854_WR_Byte(FreqWord[--count]);
		i++;
  }
	
	Freq_convert(Freq2);               //Ƶ��ת��2

	for(count=6;count>0;)	          //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(j==0)
			AD9854_WR_Byte(FREQ2);
		AD9854_WR_Byte(FreqWord[--count]);
		j++;
  }

	AD9854_WR_Byte(SHAPEI);						  //����Iͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_WR_Byte(SHAPEQ);							//����Qͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));

	AD9854_UDCLK_Set;                    //����AD9854���
  AD9854_UDCLK_Clr;		
}

//====================================================================================
//��������:void AD9854_InitBPSK(void)
//��������:AD9854��BPSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitBPSK(void)
{
	AD9854_SP_Clr;
	AD9854_WR_Clr;                 // ������д���ƶ˿���Ϊ��Ч
	AD9854_UDCLK_Clr;
	AD9854_RST_Set;                // ��λAD9854
	HAL_Delay (1);
	AD9854_RST_Clr;
	SPI_IO_RST_Clr;
	AD9854_RD_Clr;

	AD9854_WR_Byte(CONTR);
	AD9854_WR_Byte(0x10);							//�رձȽ���
	AD9854_WR_Byte(CLK_Set);					//����ϵͳʱ�ӱ�Ƶ       
	AD9854_WR_Byte(0x08);							//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x60);

	AD9854_UDCLK_Set;                //����AD9854���
  AD9854_UDCLK_Clr;
}

//====================================================================================
//��������:void AD9854_SetBPSK(uint Phase1,uint Phase2)
//��������:AD9854��BPSK����
//��ڲ���:Phase1   ������λ1
//         Phase2	������λ2
//���ڲ���:��
//˵����   ��λΪ14Bit��ȡֵ��0~16383�����꽨�����ñ�������ʱ��Phase1����Ϊ0��
//         ��Phase1����Ϊ8192��180����λ
//====================================================================================
void AD9854_SetBPSK(u16 Phasea,u16 Phaseb)
{
	u8 count;
  u8 i=0;
	const u32 Freq=60000;
  const u16 Shape=4000;

	AD9854_WR_Byte(PHASE1);										//������λ1
	AD9854_WR_Byte(Phasea>>8);
	AD9854_WR_Byte((u8)(Phasea&0xff));

	AD9854_WR_Byte(PHASE2);										//������λ2
	AD9854_WR_Byte(Phaseb>>8);
	AD9854_WR_Byte((u8)(Phaseb&0xff));
	Freq_convert(Freq);                       //Ƶ��ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(i==0)
			AD9854_WR_Byte(FREQ1);
		AD9854_WR_Byte(FreqWord[--count]);
		i++;
  }

	AD9854_WR_Byte(SHAPEI);						  			//����Iͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_WR_Byte(SHAPEQ);										//����Qͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));

	AD9854_UDCLK_Set;                         //����AD9854���
  AD9854_UDCLK_Clr;	
}

//====================================================================================
//��������:void AD9854_InitOSK(void)
//��������:AD9854��OSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitOSK(void)
{																				
	AD9854_SP_Clr;
	AD9854_WR_Clr;                 // ������д���ƶ˿���Ϊ��Ч
	AD9854_UDCLK_Clr;
	AD9854_RST_Set;                // ��λAD9854
	HAL_Delay (1);
	AD9854_RST_Clr;
	SPI_IO_RST_Clr;
	AD9854_RD_Clr;

	AD9854_WR_Byte(CONTR);
	AD9854_WR_Byte(0x10);						//�رձȽ���
	AD9854_WR_Byte(CLK_Set);				//����ϵͳʱ�ӱ�Ƶ       
	AD9854_WR_Byte(0x00);						//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x70);	          //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����,ͨ�������ڲ�����

	AD9854_UDCLK_Set;               //����AD9854���
	AD9854_UDCLK_Clr;
}

//====================================================================================
//��������:void AD9854_SetOSK(uchar RateShape)
//��������:AD9854��OSK����
//��ڲ���: RateShape    OSKб��,ȡֵΪ4~255��С��4����Ч
//���ڲ���:��
//====================================================================================
void AD9854_SetOSK(u8 RateShape)
{
	u8 count;
  u8 i=0;
	const u32 Freq=60000;			  //������Ƶ
  const u16  Shape=4000;			//��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095)

	Freq_convert(Freq);                       //Ƶ��ת��

	for(count=6;count>0;)	                    //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(i==0)
			AD9854_WR_Byte(FREQ1);
		AD9854_WR_Byte(FreqWord[--count]);
		i++;
  }

	AD9854_WR_Byte(SHAPEI);						  		  //����Iͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_WR_Byte(SHAPEQ);										//����Qͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));  	 
       
	AD9854_WR_Byte(RAMPO);										//����OSKб��
	AD9854_WR_Byte(RateShape);			          //����OSKб��

	AD9854_UDCLK_Set;                         //����AD9854���
  AD9854_UDCLK_Clr;	
}

//====================================================================================
//��������:void AD9854_InitAM(void)
//��������:AD9854��AM��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitAM(void)
{
	u8 count;
  u8 i=0;
	const u32 Freq=60000;			 //������Ƶ

	AD9854_SP_Clr;
	AD9854_WR_Clr;                 // ������д���ƶ˿���Ϊ��Ч
	AD9854_UDCLK_Clr;
	AD9854_RST_Set;                // ��λAD9854
	HAL_Delay (1);
	AD9854_RST_Clr;
	SPI_IO_RST_Clr;
	AD9854_RD_Clr;

	AD9854_WR_Byte(CONTR);
	AD9854_WR_Byte(0x10);							//�رձȽ���
	AD9854_WR_Byte(CLK_Set);					//����ϵͳʱ�ӱ�Ƶ       
	AD9854_WR_Byte(0x00);							//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x60);						  //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ���

	Freq_convert(Freq);                            //Ƶ��ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(i==0)
			AD9854_WR_Byte(FREQ1);
		AD9854_WR_Byte(FreqWord[--count]);
		i++;
  }

	AD9854_UDCLK_Set;                             //����AD9854���
	AD9854_UDCLK_Clr;
}

//====================================================================================
//��������:void AD9854_SetAM(uchar Shape)
//��������:AD9854��AM����
//��ڲ���:Shape   12Bit����,ȡֵ��0~4095   
//���ڲ���:��
//====================================================================================
void AD9854_SetAM(u16 Shape)
{
	AD9854_WR_Byte(SHAPEI);						  				//����Iͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_WR_Byte(SHAPEQ);											//����Qͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));

	AD9854_UDCLK_Set;                                   //����AD9854���
  AD9854_UDCLK_Clr;			
}

//====================================================================================
//��������:void AD9854_InitRFSK(void)
//��������:AD9854��RFSK��ʼ��
//��ڲ���:��
//���ڲ���:��
//====================================================================================
void AD9854_InitRFSK(void)
{
	AD9854_SP_Clr;
	AD9854_WR_Clr;                 // ������д���ƶ˿���Ϊ��Ч
	AD9854_UDCLK_Clr;
	AD9854_RST_Set;                // ��λAD9854
	HAL_Delay (1);
	AD9854_RST_Clr;
	SPI_IO_RST_Clr;
	AD9854_RD_Clr;
	AD9854_FDATA_Clr;

	AD9854_WR_Byte(CONTR);
	AD9854_WR_Byte(0x10);							//�رձȽ���
	AD9854_WR_Byte(CLK_Set);					//����ϵͳʱ�ӱ�Ƶ       
	AD9854_WR_Byte(0x24);							//����ϵͳΪģʽ0�����ⲿ����
	AD9854_WR_Byte(0x20);		        //����Ϊ�ɵ��ڷ��ȣ�ȡ����ֵ����,�ر�SincЧӦ	

	AD9854_UDCLK_Set;                   //����AD9854���
  AD9854_UDCLK_Clr;
}

//====================================================================================
//��������:void AD9854_SetRFSK(void)
//��������:AD9854��RFSK����
//��ڲ���:Freq_Low          RFSK��Ƶ��	   48Bit
//         Freq_High         RFSK��Ƶ��	   48Bit
//         Freq_Up_Down		 ����Ƶ��	   48Bit
//		     FreRate           б��ʱ�ӿ���  20Bit
//���ڲ���:��
//ע��     ÿ��������֮���ʱ����������ʽ��ʾ��FreRate +1��*��System Clock ����һ������,
//         Ƶ�� ���������½� һ������Ƶ��
//====================================================================================
void AD9854_SetRFSK(u32 Freq_Low,u32 Freq_High,u32 Freq_Up_Down,u32 FreRate)
{
	u8 count=6;
	u8 i=0,j=0,k=0;
  const u16  Shape=3600;			   //��������. Ϊ12 Bit,ȡֵ��ΧΪ(0~4095)

	Freq_convert(Freq_Low);                             //Ƶ��1ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(i==0)
			AD9854_WR_Byte(FREQ1);
		AD9854_WR_Byte(FreqWord[--count]);
		i++;
  }

	Freq_convert(Freq_High);                             //Ƶ��2ת��

	for(count=6;count>0;)	                         //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(j==0)
			AD9854_WR_Byte(FREQ2);
		AD9854_WR_Byte(FreqWord[--count]);
		j++;
  }

	Freq_convert(Freq_Up_Down);                             //����Ƶ��ת��

	for(count=6;count>0;)	                               //д��6�ֽڵ�Ƶ�ʿ�����  
  {
		if(k==0)
			AD9854_WR_Byte(DELFQ);
		AD9854_WR_Byte(FreqWord[--count]);
		k++;
  }

	AD9854_WR_Byte(RAMPF);						  				//����б������
	AD9854_WR_Byte((u8)((FreRate>>16)&0x0f));
	AD9854_WR_Byte((u8)(FreRate>>8));
	AD9854_WR_Byte((u8)FreRate);				    

	AD9854_WR_Byte(SHAPEI);						  				//����Iͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));
	
	AD9854_WR_Byte(SHAPEQ);											//����Qͨ������
	AD9854_WR_Byte(Shape>>8);
	AD9854_WR_Byte((u8)(Shape&0xff));

	AD9854_UDCLK_Set;                                //����AD9854���
  AD9854_UDCLK_Clr;	
}
