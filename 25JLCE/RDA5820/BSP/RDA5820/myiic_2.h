#ifndef __MYIIC_2_H
#define __MYIIC_2_H
#include "./SYSTEM/sys/sys.h"
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

   	   		   
// 假设我们要更换到 PC0(SCL) 和 PC1(SDA)

//------------------ 第二个 I2C 的宏定义 ------------------
// PB7(SDA) 输入/输出模式配置（PB7 在 CRL 寄存器，位 28-31）
#define SDA_IN_2()  {GPIOB->CRL &= 0x0FFFFFFF; GPIOB->CRL |= 8 << 28;}  // 输入模式 (0b1000)
#define SDA_OUT_2() {GPIOB->CRL &= 0x0FFFFFFF; GPIOB->CRL |= 3 << 28;}  // 推挽输出 (0b0011)

// IO 操作宏
#define IIC_SCL_2    PBout(6)  // SCL = PB6
#define IIC_SDA_2    PBout(7)  // SDA = PB7
#define READ_SDA_2   PBin(7)   // 读取 SDA = PB7

// //IO��������
// #define SDA_IN_2()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
// #define SDA_OUT_2() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

// //IO��������	 
// #define IIC_SCL_2    PBout(10) //SCL
// #define IIC_SDA_2    PBout(11) //SDA	 
// #define READ_SDA_2   PBin(11)  //����SDA 


//IIC���в�������
void IIC_Init_2(void);                //��ʼ��IIC��IO��				 
void IIC_Start_2(void);				//����IIC��ʼ�ź�
void IIC_Stop_2(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte_2(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte_2(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack_2(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack_2(void);					//IIC����ACK�ź�
void IIC_NAck_2(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte_2(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_2(u8 daddr,u8 addr);	  
#endif
















