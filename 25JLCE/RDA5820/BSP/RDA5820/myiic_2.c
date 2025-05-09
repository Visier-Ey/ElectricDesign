#include "myiic_2.h"
#include "./SYSTEM/delay/delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//��ʼ��IIC
// void IIC_Init_2(void)
// {					     
//  	RCC->APB2ENR|=1<<3;//��ʹ������IO PORTBʱ�� 							 
// 	GPIOB->CRH&=0XFFFF00FF;//PB1/11 �������
// 	GPIOB->CRH|=0X00003300;	   
// 	GPIOB->ODR|=3<<10;     //PB10,11 �����
// }
void IIC_Init_2(void)
{
    // 1. 使能 GPIOB 时钟（如果之前没开启）
    RCC->APB2ENR |= 1 << 3; // GPIOB 时钟使能（和第一个 I2C 共用）
    
    // 2. 配置 PB6(SCL) 和 PB7(SDA)（PB6/PB7 在 CRL 寄存器）
    GPIOB->CRL &= 0x00FFFFFF; // 清除 PB6（位 24-27）和 PB7（位 28-31）
    GPIOB->CRL |= 0x33000000; // PB6 和 PB7 推挽输出（0b0011）
    
    // 3. 设置 PB6 和 PB7 默认高电平（上拉）
    GPIOB->ODR |= (1 << 6) | (1 << 7); // PB6(SCL) 和 PB7(SDA) 上拉
}

//����IIC��ʼ�ź�
void IIC_Start_2(void)
{
	SDA_OUT_2();     //sda�����
	IIC_SDA_2=1;	  	  
	IIC_SCL_2=1;
	delay_us(4);
 	IIC_SDA_2=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_2=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_2(void)
{
	SDA_OUT_2();//sda�����
	IIC_SCL_2=0;
	IIC_SDA_2=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_2=1; 
	IIC_SDA_2=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack_2(void)
{
	u8 ucErrTime=0;
	SDA_IN_2();      //SDA����Ϊ����  
	IIC_SDA_2=1;delay_us(1);	   
	IIC_SCL_2=1;delay_us(1);	 
	while(READ_SDA_2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_2();
			return 1;
		}
	}
	IIC_SCL_2=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void IIC_Ack_2(void)
{
	IIC_SCL_2=0;
	SDA_OUT_2();
	IIC_SDA_2=0;
	delay_us(2);
	IIC_SCL_2=1;
	delay_us(2);
	IIC_SCL_2=0;
}
//������ACKӦ��		    
void IIC_NAck_2(void)
{
	IIC_SCL_2=0;
	SDA_OUT_2();
	IIC_SDA_2=1;
	delay_us(2);
	IIC_SCL_2=1;
	delay_us(2);
	IIC_SCL_2=0;
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_2(u8 txd)
{                        
    u8 t;   
	SDA_OUT_2(); 	    
    IIC_SCL_2=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        IIC_SDA_2=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_2=1;
		delay_us(2); 
		IIC_SCL_2=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte_2(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_2();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL_2=0; 
        delay_us(2);
		IIC_SCL_2=1;
        receive<<=1;
        if(READ_SDA_2)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck_2();//����nACK
    else
        IIC_Ack_2(); //����ACK   
    return receive;
}



























