#include "rda5820.h"
#include "./SYSTEM/delay/delay.h"
#include "myiic.h"

#include "./SYSTEM/usart/usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//RDA5820 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//��ʼ��
//0,��ʼ���ɹ�;
//����,��ʼ��ʧ��.

u16 freq[50]={0};
u8 Rssi[50]={0};
u8 num=0;


u8 RDA5820_Init(void)
{
	u16 id;
	IIC_Init();						//��ʼ��IIC��	
	id=RDA5820_RD_Reg(RDA5820_R00);	//��ȡID =0X5805
	// printf("%x\r\n",id);
	
	if(id==0X5805||id==0X5820)					//��ȡID��ȷ
	{
	 	RDA5820_WR_Reg(RDA5820_R02,0x0002);	//����λ
		delay_ms(50);
	 	RDA5820_WR_Reg(RDA5820_R02,0xC001);	//������,�ϵ�    1001  9   1010  a   1011b   1100  c    1101  d    1110  e  1111   f
		delay_ms(600);						//�ȴ�ʱ���ȶ� 
	 	RDA5820_WR_Reg(RDA5820_R05,0X884F);	//����ǿ��8,LNAN,1.8mA,VOL���
	 	RDA5820_WR_Reg(0X07,0X7800);		// 
	 	RDA5820_WR_Reg(0X13,0X0008);		// 
	 	RDA5820_WR_Reg(0X15,0x1420);		//VCO����  0x17A0/0x1420 
	 	RDA5820_WR_Reg(0X16,0XC000);		//  
	 	RDA5820_WR_Reg(0X1C,0X3126);		// 
	 	RDA5820_WR_Reg(0X22,0X9C24);		//fm_true 
	 	RDA5820_WR_Reg(0X47,0XF660) ;		//tx rds 
	}else return 1;//��ʼ��ʧ��
	return 0;
}
//дRDA5820�Ĵ���						 				    
void RDA5820_WR_Reg(u8 addr,u16 val)
{
    IIC_Start();  			   
	IIC_Send_Byte(RDA5820_WRITE);	//����д����   	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(addr);   			//���͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(val>>8);     		//���͸��ֽ�							   
	IIC_Wait_Ack();  		    	   
 	IIC_Send_Byte(val&0XFF);     	//���͵��ֽ�							   
 	IIC_Wait_Ack();  		    	   
    IIC_Stop();						//����һ��ֹͣ���� 	 
}
//��RDA5820�Ĵ���	
u16 RDA5820_RD_Reg(u8 addr)
{
	u16 res;
    IIC_Start();  			   
	IIC_Send_Byte(RDA5820_WRITE);	//����д����   	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(addr);   			//���͵�ַ
	IIC_Wait_Ack(); 	 										  		   
    IIC_Start();  			   
	IIC_Send_Byte(RDA5820_READ);    //���Ͷ�����							   
	IIC_Wait_Ack();  		    	   
 	res=IIC_Read_Byte(1);     		//�����ֽ�,����ACK	  
  	res<<=8;
  	res|=IIC_Read_Byte(0);     		//�����ֽ�,����NACK							   
  	IIC_Stop();						//����һ��ֹͣ���� 
	return res;						//���ض���������
}
//����RDA5820ΪRXģʽ
void RDA5820_RX_Mode(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X40);		//��ȡ0X40������
	temp&=0xfff0;					//RX ģʽ   
	RDA5820_WR_Reg(0X40,temp) ;		//FM RXģʽ 
}			
//����RDA5820ΪTXģʽ
void RDA5820_TX_Mode(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X40);		//��ȡ0X40������
	temp&=0xfff0;
	temp|=0x0001;				    //TX ģʽ
	RDA5820_WR_Reg(0X40,temp) ;		//FM TM ģʽ 
}

//�õ��ź�ǿ��
//����ֵ��Χ:0~127
u8 RDA5820_Rssi_Get(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X0B);		//��ȡ0X0B������
	return temp>>9;                 //�����ź�ǿ��
}
//��������ok
//vol:0~15;
void RDA5820_Vol_Set(u8 vol)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X05);		//��ȡ0X05������
	temp&=0XFFF0;
	temp|=vol&0X0F;				   		 
	RDA5820_WR_Reg(0X05,temp) ;		//��������	
}
//��������
//mute:0,������;1,����
void RDA5820_Mute_Set(u8 mute)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X02);		//��ȡ0X02������
	if(mute)temp|=1<<13;
	else temp&=~(1<<13);	    		   		 
	RDA5820_WR_Reg(0X02,temp) ;		//����MUTE	
}
//����������
//rssi:0~127;
void RDA5820_Rssi_Set(u8 rssi)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X05);		//��ȡ0X05������
	temp&=0X80FF;
	temp|=(u16)rssi<<8;				   		 
	RDA5820_WR_Reg(0X05,temp) ;		//����RSSI	
}
//����TX���͹���
//gain:0~63
void RDA5820_TxPAG_Set(u8 gain)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X42);		//��ȡ0X42������
	temp&=0XFFC0;
	temp|=gain;				   		//GAIN
	RDA5820_WR_Reg(0X42,temp) ;		//����PA�Ĺ���
}
//����TX �����ź�����
//gain:0~7
void RDA5820_TxPGA_Set(u8 gain)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X42);		//��ȡ0X42������
	temp&=0XF8FF;
	temp|=gain<<8;			    	//GAIN
	RDA5820_WR_Reg(0X42,temp) ;		//����PGA
}
//����RDA5820�Ĺ���Ƶ��
//band:0,87~108Mhz;1,76~91Mhz;2,76~108Mhz;3,�û��Զ���(53H~54H)
void RDA5820_Band_Set(u8 band)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X03);		//��ȡ0X03������
	temp&=0XFFF3;
	temp|=band<<2;			     
	RDA5820_WR_Reg(0X03,temp) ;		//����BAND
}
//����RDA5820�Ĳ���Ƶ��
//band:0,100Khz;1,200Khz;2,50Khz;3,����
void RDA5820_Space_Set(u8 spc)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X03);		//��ȡ0X03������
	temp&=0XFFFC;
	temp|=spc;			     
	RDA5820_WR_Reg(0X03,temp) ;		//����BAND
}
//����RDA5820��Ƶ��
//freq:Ƶ��ֵ(��λΪ10Khz),����10805,��ʾ108.05Mhz
void RDA5820_Freq_Set(u16 freq)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);	//��ȡ0X03������
	temp&=0X001F;
	band=(temp>>2)&0x03;		//�õ�Ƶ��
	spc=temp&0x03; 				//�õ��ֱ���
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//�õ�bottomƵ��
		fbtm*=10;
	}
	if(freq<fbtm)return;
	chan=(freq-fbtm)/spc;		//�õ�CHANӦ��д���ֵ
	chan&=0X3FF;				//ȡ��10λ	  
	temp|=chan<<6;
	temp|=1<<4;					//TONE ENABLE			     
	RDA5820_WR_Reg(0X03,temp) ;	//����Ƶ��
	delay_ms(20);				//�ȴ�20ms
	while((RDA5820_RD_Reg(0X0B)&(1<<7))==0);//�ȴ�FM_READY
	
}
//�õ���ǰƵ��
//����ֵ:Ƶ��ֵ(��λ10Khz)
u16 RDA5820_Freq_Get(void)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);		//��ȡ0X03������
	chan=temp>>6;   
	band=(temp>>2)&0x03;		//�õ�Ƶ��
	spc=temp&0x03; 				//�õ��ֱ���
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//�õ�bottomƵ��
		fbtm*=10;
	}
 	temp=fbtm+chan*spc;				 
	return temp;//����Ƶ��ֵ  
}

//�õ���̨Ƶ��
u16 RDA5820_Freq_Gets(void)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);		//��ȡ0X03������
	chan=RDA5820_RD_Reg(0X0A)&0X00FF;		//��ȡ0X0A������  
	band=(temp>>2)&0x03;		//�õ�Ƶ��
	spc=temp&0x03; 				//�õ��ֱ���
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//�õ�bottomƵ��
		fbtm*=10;
	}
 	temp=fbtm+chan*spc;	
	
	return temp;//����Ƶ��ֵ
}
//��̨
void RdaSeek(void)
{
u16 SF;
u16 FM_TRUE;
u16 STC;
u16 rssi;
    u8 i=0;
	RDA5820_Rssi_Set(8);
    RDA5820_WR_Reg(0X53,650);
    RDA5820_WR_Reg(0X54,1150);
	RDA5820_WR_Reg(RDA5820_R40,0X0000) ;  //����
	RDA5820_WR_Reg(RDA5820_R03,0X0158) ;	//Ƶ�� ����    0000 0001 0101 1100  100K
	RDA5820_WR_Reg(RDA5820_R02,0XD381) ;	            //1101  0011 1000 0001 
	SF=RDA5820_RD_Reg(RDA5820_R0A)&0X2000;
	FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
	STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
	rssi=RDA5820_Rssi_Get();


while(FM_TRUE!=0){
		RDA5820_WR_Reg(RDA5820_R02,0XD381) ;   
	
		freq[i]=RDA5820_Freq_Gets();
		printf("FREQ=%d\r\n\r",freq[i]);
		delay_ms(10);		
		STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
		printf("STC=%x\r\n",STC);		
		SF=RDA5820_RD_Reg(RDA5820_R0A)&0X2000;
		printf("SF=%x\r\n",SF);
		FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
		printf("FM_TRUE=%x\r\n",FM_TRUE);
		Rssi[i]=RDA5820_Rssi_Get();
		printf("RSSI=%d\r\n\r",rssi);
    
        i++;num++;

	}

    
    
    
}

//��̨
//u16 RdaSeek1(u8 std)
//{
//u16 chan;
//u16	freqget;
//u16	true_freqget=0;
//u16 value;
//u16 FM_TRUE;
//u16 STC;
//u16 rssi;
//u8 i=1;
//chan=0x0005;
//value=(chan<<6)+0x0010;
//RDA5820_WR_Reg(RDA5820_R03,value) ;	//Ƶ�� ����
//while(i){	
//	delay_ms(50);
//	do{STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
//			printf("STC=%x\r\n",STC);		
//	FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
//    printf("FM_TRUE=%x\r\n",FM_TRUE);
//		delay_ms(20);
//	}while(STC==0);
//	
//	freqget=RDA5820_Freq_Gets();
//	printf("FREQ=%d\r\n\r",freqget);
//    rssi=RDA5820_Rssi_Get();
//		printf("RSSI=%d\r\n\r",rssi);
////	LCD_ShowxNum(60,10,RDA5820_Rssi_Get(),9,16,0);
//	if(rssi>std){
//		true_freqget=freqget;
//		i=0;
////		LCD_ShowxNum(60,120,true_freqget,9,16,0);
//		printf("FREQ_true=%d\r\n\r",freqget);		
//		}
//	chan++;
//	value=(chan<<6)+0x0010;
//	RDA5820_WR_Reg(RDA5820_R03,value) ;	//Ƶ�� ����
//if(freqget>10800){
//	i=0;
////LCD_ShowxNum(60,120,true_freqget,9,16,0);}

//}

//	
//return true_freqget;
//}



//void MyRdaSeek(void)
//{
//u16 SF;
//u16 FM_TRUE;
//u16 STC;
//u16 rssi;
//uint8_t  i=0;
//	RDA5820_Rssi_Set(8);
//    RDA5820_WR_Reg(0X53,650);
//    RDA5820_WR_Reg(0X54,1150);
//	RDA5820_WR_Reg(RDA5820_R40,0X0000) ;  //����
//	RDA5820_WR_Reg(RDA5820_R03,0X015c) ;	//Ƶ�� ����    0000 0001 0101 1100  100K
//	RDA5820_WR_Reg(RDA5820_R02,0XD381) ;	            //1101  0011 1000 0001 
//	SF=RDA5820_RD_Reg(RDA5820_R0A)&0X2000;
//	FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
//	STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
//	rssi=RDA5820_Rssi_Get();

//while(1){
//		RDA5820_WR_Reg(RDA5820_R02,0XD381) ;
//        

//		delay_ms(10);
//        while((RDA5820_RD_Reg(RDA5820_R0A)&0X4000)==0);
//        
//        STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
//		printf("STC=%x\r\n",STC);		
//		SF=RDA5820_RD_Reg(RDA5820_R0A)&0X2000;
//		printf("SF=%x\r\n",SF);
//		FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
//		printf("FM_TRUE=%x\r\n",FM_TRUE);
//		rssi=RDA5820_Rssi_Get();
//		printf("RSSI=%d\r\n\r",rssi);
//    if(SF==1||FM_TRUE==0)
//        break;
//    else
//    {
//        freq[i]=RDA5820_Freq_Gets();
//        Rssi[i]=rssi;
//        i++;num++;
//        
//    }
//	}}

//void MyRdaSeek1(void)
//{
//u16 SF;
//u16 FM_TRUE;
//u16 STC;
//u16 rssi,freqget;
//uint8_t  i=0;
//	RDA5820_Rssi_Set(8);
//    RDA5820_WR_Reg(0X53,650);
//    RDA5820_WR_Reg(0X54,1150);
//	RDA5820_WR_Reg(RDA5820_R40,0X0000) ;  //����
//	RDA5820_WR_Reg(RDA5820_R03,0X015c) ;	//Ƶ�� ����    0000 0001 0101 1100  100K
//	RDA5820_WR_Reg(RDA5820_R02,0XD381) ;	            //1101  0011 1000 0001 
//	SF=RDA5820_RD_Reg(RDA5820_R0A)&0X2000;
//	FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
//	STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
//	rssi=RDA5820_Rssi_Get();
//    RDA5820_Freq_Set(8500);
//while(1){
//        

//		delay_ms(10);
//        while((RDA5820_RD_Reg(RDA5820_R0B)&0X0080)==0)  ;
//        
//        STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
//		printf("STC=%x\r\n",STC);		
//		SF=RDA5820_RD_Reg(RDA5820_R0A)&0X2000;
//		printf("SF=%x\r\n",SF);
//		FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
//		printf("FM_TRUE=%x\r\n",FM_TRUE);
//		rssi=RDA5820_Rssi_Get();
//		printf("RSSI=%d\r\n\r",rssi);
//    
//    	freqget=RDA5820_Freq_Gets();
//     printf("%d\r\n",freqget);
//    if(freqget>8900)
//        break;
//    else  if(FM_TRUE==256)
//    {
//        freq[i]=RDA5820_Freq_Gets();
//        Rssi[i]=rssi;
//        i++;num++;
//        		printf("NUM=%d\tRssi=%d\r\n\r",num,rssi);

//  		RDA5820_WR_Reg(RDA5820_R02,0XD381) ;

//        
//    }
//    
//    else
//  	RDA5820_WR_Reg(RDA5820_R02,0XD381) ;

//	}}







    
    //��̨
void HardSeek(void)
{
u16 SF;
u16 FM_TRUE;
u16 STC;
u16 fre;
u8 i=0;
    
    RDA5820_WR_Reg(RDA5820_R03,0X0158) ;	//Ƶ�� ����    0000 0001 0101 1100  100K
    
    do{

    RDA5820_WR_Reg(RDA5820_R02,0XD381) ;	            //1101  0011 1000 0001 

    delay_ms(10);
    while((RDA5820_RD_Reg(RDA5820_R0A)&0X4000)==0&&(RDA5820_RD_Reg(0X0B)&(1<<7))==0);

        
        SF=RDA5820_RD_Reg(RDA5820_R0A)&0X2000;
        FM_TRUE=RDA5820_RD_Reg(RDA5820_R0B)&0X0100;
        STC=RDA5820_RD_Reg(RDA5820_R0A)&0X4000;
        freq[i]=RDA5820_Freq_Gets();
        printf("FREQ=%d\r\n\r",freq[i]);
        printf("STC=%x\r\n",STC);
        printf("SF=%x\r\n",SF);
        printf("FM_TRUE=%x\r\n",FM_TRUE);
        Rssi[i]=RDA5820_Rssi_Get();
        printf("RSSI=%d\r\n\r",Rssi[i]);i++;num++;
        
    }    while(((RDA5820_RD_Reg(RDA5820_R0A)&0X2000)==1)||((RDA5820_RD_Reg(RDA5820_R0B)&0X0100)==0));
        
        printf("SEEK Finishe!!\r\n");
        
    
}


void SoftSeek(void)
{
        u16 FM_TRUE;
        u8 i=0;
        u16 set_freq=7600;
        u16 reg_value;
       RDA5820_WR_Reg(RDA5820_R03,0X0158) ;	//Ƶ�� ����    0000 0001 0101 1100  100K

       do{
           
        delay_ms(10);
	    while((RDA5820_RD_Reg(0X0B)&(1<<7))==0);//�ȴ�FM_READY
           
           
     if(RDA5820_RD_Reg(RDA5820_R0B)&0X0100)
        {
            Rssi[i]=RDA5820_Rssi_Get();
            freq[i]=RDA5820_Freq_Gets();
            
            printf("RSSI=%d\r\n\r",Rssi[i]);
            printf("FREQ=%d\r\n\r",freq[i]);
            i++;num++;
                    //TUNEλ��һ
        reg_value = RDA5820_RD_Reg(RDA5820_R03);
        // ��������λ���䣬��λ4����Ϊ1
        reg_value |= (1 << 4);
        // д��Ĵ���
        RDA5820_WR_Reg(RDA5820_R03, reg_value);
        }
        
        set_freq +=10;
        RDA5820_Freq_Set(set_freq);

        printf("set_freq:%d!!\r\n",set_freq);


        
}while(set_freq<9000);
       
        printf("SEEK Finishe!!\r\n");
}






















