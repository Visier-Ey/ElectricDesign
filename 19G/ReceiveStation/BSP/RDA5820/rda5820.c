#include "rda5820.h"
#include "./SYSTEM/delay/delay.h"
#include "myiic.h"

#include "./SYSTEM/usart/usart.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//RDA5820 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/14
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//初始化
//0,初始化成功;
//其他,初始化失败.

u16 freq[50]={0};
u8 Rssi[50]={0};
u8 num=0;


u8 RDA5820_Init(void)
{
	u16 id;
	IIC_Init();						//初始化IIC口	
	id=RDA5820_RD_Reg(RDA5820_R00);	//读取ID =0X5805
	printf("%x\r\n",id);
	
	if(id==0X5805||id==0X5820)					//读取ID正确
	{
	 	RDA5820_WR_Reg(RDA5820_R02,0x0002);	//软复位
		delay_ms(50);
	 	RDA5820_WR_Reg(RDA5820_R02,0xC001);	//立体声,上电    1001  9   1010  a   1011b   1100  c    1101  d    1110  e  1111   f
		delay_ms(600);						//等待时钟稳定 
//	 	RDA5820_WR_Reg(RDA5820_R05,0X884F);	//搜索强度8,LNAN,1.8mA,VOL最大
// 	 	RDA5820_WR_Reg(0X07,0X7800);		// 
//	 	RDA5820_WR_Reg(0X13,0X0008);		// 
//	 	RDA5820_WR_Reg(0X15,0x1420);		//VCO设置  0x17A0/0x1420 
//	 	RDA5820_WR_Reg(0X16,0XC000);		//  
//	 	RDA5820_WR_Reg(0X1C,0X3126);		// 
//	 	RDA5820_WR_Reg(0X22,0X9C24);		//fm_true 
//	 	RDA5820_WR_Reg(0X47,0XF660) ;		//tx rds 
 	}else return 1;//初始化失败
	return 0;
}
//写RDA5820寄存器						 				    
void RDA5820_WR_Reg(u8 addr,u16 val)
{
    IIC_Start();  			   
	IIC_Send_Byte(RDA5820_WRITE);	//发送写命令   	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(addr);   			//发送地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(val>>8);     		//发送高字节							   
	IIC_Wait_Ack();  		    	   
 	IIC_Send_Byte(val&0XFF);     	//发送低字节							   
 	IIC_Wait_Ack();  		    	   
    IIC_Stop();						//产生一个停止条件 	 
}
//读RDA5820寄存器	
u16 RDA5820_RD_Reg(u8 addr)
{
	u16 res;
    IIC_Start();  			   
	IIC_Send_Byte(RDA5820_WRITE);	//发送写命令   	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(addr);   			//发送地址
	IIC_Wait_Ack(); 	 										  		   
    IIC_Start();  			   
	IIC_Send_Byte(RDA5820_READ);    //发送读命令							   
	IIC_Wait_Ack();  		    	   
 	res=IIC_Read_Byte(1);     		//读高字节,发送ACK	  
  	res<<=8;
  	res|=IIC_Read_Byte(0);     		//读低字节,发送NACK							   
  	IIC_Stop();						//产生一个停止条件 
	return res;						//返回读到的数据
}
//设置RDA5820为RX模式
void RDA5820_RX_Mode(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X40);		//读取0X40的内容
	temp&=0xfff0;					//RX 模式   
	RDA5820_WR_Reg(0X40,temp) ;		//FM RX模式 
}			
//设置RDA5820为TX模式
void RDA5820_TX_Mode(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X40);		//读取0X40的内容
	temp&=0xfff0;
	temp|=0x0001;				    //TX 模式
	RDA5820_WR_Reg(0X40,temp) ;		//FM TM 模式 
}

//得到信号强度
//返回值范围:0~127
u8 RDA5820_Rssi_Get(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X0B);		//读取0X0B的内容
	return temp>>9;                 //返回信号强度
}
//设置音量ok
//vol:0~15;
void RDA5820_Vol_Set(u8 vol)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X05);		//读取0X05的内容
	temp&=0XFFF0;
	temp|=vol&0X0F;				   		 
	RDA5820_WR_Reg(0X05,temp) ;		//设置音量	
}
//静音设置
//mute:0,不静音;1,静音
void RDA5820_Mute_Set(u8 mute)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X02);		//读取0X02的内容
	if(mute)temp|=1<<13;
	else temp&=~(1<<13);	    		   		 
	RDA5820_WR_Reg(0X02,temp) ;		//设置MUTE	
}
//设置灵敏度
//rssi:0~127;
void RDA5820_Rssi_Set(u8 rssi)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X05);		//读取0X05的内容
	temp&=0X80FF;
	temp|=(u16)rssi<<8;				   		 
	RDA5820_WR_Reg(0X05,temp) ;		//设置RSSI	
}
//设置TX发送功率
//gain:0~63
void RDA5820_TxPAG_Set(u8 gain)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X42);		//读取0X42的内容
	temp&=0XFFC0;
	temp|=gain;				   		//GAIN
	RDA5820_WR_Reg(0X42,temp) ;		//设置PA的功率
}
//设置TX 输入信号增益
//gain:0~7
void RDA5820_TxPGA_Set(u8 gain)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X42);		//读取0X42的内容
	temp&=0XF8FF;
	temp|=gain<<8;			    	//GAIN
	RDA5820_WR_Reg(0X42,temp) ;		//设置PGA
}
//设置RDA5820的工作频段
//band:0,87~108Mhz;1,76~91Mhz;2,76~108Mhz;3,用户自定义(53H~54H)
void RDA5820_Band_Set(u8 band)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X03);		//读取0X03的内容
	temp&=0XFFF3;
	temp|=band<<2;			     
	RDA5820_WR_Reg(0X03,temp) ;		//设置BAND
}
//设置RDA5820的步进频率
//band:0,100Khz;1,200Khz;2,50Khz;3,保留
void RDA5820_Space_Set(u8 spc)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X03);		//读取0X03的内容
	temp&=0XFFFC;
	temp|=spc;			     
	RDA5820_WR_Reg(0X03,temp) ;		//设置BAND
}
//设置RDA5820的频率
//freq:频率值(单位为10Khz),比如10805,表示108.05Mhz
void RDA5820_Freq_Set(u16 freq)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);	//读取0X03的内容
	temp&=0X001F;
	band=(temp>>2)&0x03;		//得到频带
	spc=temp&0x03; 				//得到分辨率
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//得到bottom频率
		fbtm*=10;
	}
	if(freq<fbtm)return;
	chan=(freq-fbtm)/spc;		//得到CHAN应该写入的值
	chan&=0X3FF;				//取低10位	  
	temp|=chan<<6;
	temp|=1<<4;					//TONE ENABLE			     
	RDA5820_WR_Reg(0X03,temp) ;	//设置频率
	delay_ms(20);				//等待20ms
	while((RDA5820_RD_Reg(0X0B)&(1<<7))==0);//等待FM_READY
	
}
//得到当前频率
//返回值:频率值(单位10Khz)
u16 RDA5820_Freq_Get(void)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);		//读取0X03的内容
	chan=temp>>6;   
	band=(temp>>2)&0x03;		//得到频带
	spc=temp&0x03; 				//得到分辨率
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//得到bottom频率
		fbtm*=10;
	}
 	temp=fbtm+chan*spc;				 
	return temp;//返回频率值  
}

//得到搜台频率
u16 RDA5820_Freq_Gets(void)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);		//读取0X03的内容
	chan=RDA5820_RD_Reg(0X0A)&0X00FF;		//读取0X0A的内容  
	band=(temp>>2)&0x03;		//得到频带
	spc=temp&0x03; 				//得到分辨率
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//得到bottom频率
		fbtm*=10;
	}
 	temp=fbtm+chan*spc;	
	
	return temp;//返回频率值
}
//搜台
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
	RDA5820_WR_Reg(RDA5820_R40,0X0000) ;  //接收
	RDA5820_WR_Reg(RDA5820_R03,0X0158) ;	//频段 步进    0000 0001 0101 1100  100K
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

//搜台
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
//RDA5820_WR_Reg(RDA5820_R03,value) ;	//频段 步进
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
//	RDA5820_WR_Reg(RDA5820_R03,value) ;	//频段 步进
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
//	RDA5820_WR_Reg(RDA5820_R40,0X0000) ;  //接收
//	RDA5820_WR_Reg(RDA5820_R03,0X015c) ;	//频段 步进    0000 0001 0101 1100  100K
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
//	RDA5820_WR_Reg(RDA5820_R40,0X0000) ;  //接收
//	RDA5820_WR_Reg(RDA5820_R03,0X015c) ;	//频段 步进    0000 0001 0101 1100  100K
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







    
    //搜台
void HardSeek(void)
{
u16 SF;
u16 FM_TRUE;
u16 STC;
u16 fre;
u8 i=0;
    
    RDA5820_WR_Reg(RDA5820_R03,0X0158) ;	//频段 步进    0000 0001 0101 1100  100K
    
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
       RDA5820_WR_Reg(RDA5820_R03,0X0158) ;	//频段 步进    0000 0001 0101 1100  100K

       do{
           
        delay_ms(10);
	    while((RDA5820_RD_Reg(0X0B)&(1<<7))==0);//等待FM_READY
           
           
     if(RDA5820_RD_Reg(RDA5820_R0B)&0X0100)
        {
            Rssi[i]=RDA5820_Rssi_Get();
            freq[i]=RDA5820_Freq_Gets();
            
            printf("RSSI=%d\r\n\r",Rssi[i]);
            printf("FREQ=%d\r\n\r",freq[i]);
            i++;num++;
                    //TUNE位置一
        reg_value = RDA5820_RD_Reg(RDA5820_R03);
        // 保持其他位不变，将位4设置为1
        reg_value |= (1 << 4);
        // 写入寄存器
        RDA5820_WR_Reg(RDA5820_R03, reg_value);
        }
        
        set_freq +=10;
        RDA5820_Freq_Set(set_freq);

        printf("set_freq:%d!!\r\n",set_freq);


        
}while(set_freq<9000);
       
        printf("SEEK Finishe!!\r\n");
}






















