#ifndef __RDA5820_H
#define __RDA5820_H	 
#include "./SYSTEM/sys/sys.h"
#include "myiic.h"   
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

#define RDA5820_R00		0X00  //����16��λ��ID =0X5820
#define RDA5820_R02		0X02  //DHIZ[15],DMUTE[14],MONO[13],BASS[12],SEEKUP[9],SEEK[8],SKMODE[7],CLK_MODE[6:4],ANTENNA[2],SOFTRESET[1],ENABLE[0]
#define RDA5820_R03		0X03  //CHAN[15:6],TUNE[4],BAND[3:2],SPACE[1:0]
#define RDA5820_R04		0X04  //STCIEN[14](��������ж�),DE[11],I2S_ENABLE[6],GPIO3~1[5:0]
#define RDA5820_R05		0X05  //INT_MODE[15],SEEKTH[14:8](�趨�ź�ǿ��),LNA_PORT_SEL[7:6],LNA_ICSEL_BIT[5:4],VOLUME[3:0];
#define RDA5820_R0A		0X0A  //STC[14](������ɱ�־),SF[13](����ʧ�ܱ�־),ST[10](��������־),READCHAN[9:0](Ƶ��).
#define RDA5820_R0B		0X0B  //RSSI[15:9](�ź�ǿ��),FM_TRUE[8](վ���־),FM_READY[7](fm������־)
#define RDA5820_R40		0X40  //AUTO_SEEK[15](ȫ/���Զ���̨),CHAN_SCAN[14](�ѿ�/æ̨),CHIP_FUN[3:0](����ģʽ)
#define RDA5820_R41		0X41  //MEM_CLR[15](�ڴ����),RPT_TIME[14:9](RDSӦ�����),MEM_DEPTH[8:0](FIFO��С,���256)
#define RDA5820_R42		0X42  //TX_SIG_GAIN[10:8],TX_PA_GAIN[5:0](���书��).
#define RDA5820_R4A		0X4A  //MEM_INTMOD[4:0]
#define RDA5820_R4B		0X4B  //CHAN_NUM[7:0](����ȫ�Զ���̨��Ч,������̨����).
#define RDA5820_R4C		0X4C  //TX_AUDIO_DEV[15:0]
#define RDA5820_R4D		0X4D  //TX_PILOT_DEV[15:0]
#define RDA5820_R4E		0X4E  //TX_RDS_DEV[15:0]
#define RDA5820_R53		0X53  //CHAN_BOTTON[10:0](ͨ�����Ƶ��,100kHZΪ��λ)
#define RDA5820_R54		0X54  //CHAN_TOP[10:0](ͨ�����Ƶ��,100kHZΪ��λ)
#define RDA5820_R64		0X64  //RDS_RXMOD[4:3](FIFOģʽ[10]���߼Ĵ���ģʽ[11])		 

#define RDA5820_READ    0X23  //��RDA5820
#define RDA5820_WRITE	0X22  //дRDA5820

extern u16 freq[50];
extern u8 Rssi[50];
extern u8 num;


u8 RDA5820_Init(void);					//��ʼ��		 				    
void RDA5820_WR_Reg(u8 addr,u16 val);	//дRDA5820�Ĵ���
u16 RDA5820_RD_Reg(u8 addr);			//��RDA5820�Ĵ���
void RDA5820_RX_Mode(void);				//����RDA5820ΪRXģʽ
void RDA5820_TX_Mode(void);				//����RDA5820ΪTXģʽ
u8 RDA5820_Rssi_Get(void);
void RDA5820_Mute_Set(u8 mute);
void RDA5820_Rssi_Set(u8 rssi);
void RDA5820_Vol_Set(u8 vol);
void RDA5820_TxPAG_Set(u8 gain);
void RDA5820_TxPGA_Set(u8 gain);
void RDA5820_Band_Set(u8 band);
void RDA5820_Space_Set(u8 spc);
void RDA5820_Freq_Set(u16 freq);
u16 RDA5820_Freq_Gets(void);

u16 RDA5820_Freq_Get(void);
void RdaSeek(void);
u16 RdaSeek1(u8 std);
void MyRdaSeek(void);
void MyRdaSeek1(void);
void HardSeek(void);
void SoftSeek(void);





		 				    
#endif































