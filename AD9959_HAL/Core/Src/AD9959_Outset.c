#include "AD9959_Outset.h"
#include "AD9959.h"

//--------ͨ���Ĵ�����ַ�궨��---------------//
#define CSR 0x00               //ͨ��ѡ��Ĵ���
#define FR1 0x01               //���ܼĴ���1
#define FR2 0x02               //���ܼĴ���2
#define CFR 0x03               //ͨ�����ܼĴ���
#define CFTW0 0x04             //32λͨ��Ƶ��ת���ּĴ���
#define CPOW0 0x05             //14λͨ����λת���ּĴ���
#define ACR 0x06               //���ȿ��ƼĴ���
#define SRR 0x07               //����ɨ�趨ʱ��
#define RDW 0x08               //��������ɨ�趨ʱ��
#define FDW 0x09               //��������ɨ�趨ʱ��



#define uchar unsigned char
#define uint unsigned int



	void AD9959_enablechannel0(void)                    //ͨ��0ʹ��
	{
		uchar ChannelSelectRegisterdata0[1] =  {0x10};   // ͨ��ѡ��Ĵ�����3�ߴ��䣬���ݸ�λ����
																				
	  WriteToAD9959ViaSpi(CSR,1,ChannelSelectRegisterdata0,0); 
	}
	
	void AD9959_enablechannel1(void)                   //ͨ��1ʹ��
	{
		uchar ChannelSelectRegisterdata1[1] = {0x20};   // ͨ��ѡ��Ĵ�����3�ߴ��䣬���ݸ�λ���� 
																								  // SDIO0 �������� and SDIO2 �������
		WriteToAD9959ViaSpi(CSR,1,ChannelSelectRegisterdata1,0); 
	}
	void AD9959_enablechannel2(void)                   //ͨ��1ʹ��
	{
		uchar ChannelSelectRegisterdata2[1] = {0x40};   // ͨ��ѡ��Ĵ�����3�ߴ��䣬���ݸ�λ���� 
																								  // SDIO0 �������� and SDIO2 �������
		WriteToAD9959ViaSpi(CSR,1,ChannelSelectRegisterdata2,0); 
	}
	void AD9959_enablechannel3(void)                   //ͨ��1ʹ��
	{
		uchar ChannelSelectRegisterdata3[1] = {0x80};   // ͨ��ѡ��Ĵ�����3�ߴ��䣬���ݸ�λ���� 
																									  // SDIO0 �������� and SDIO2 �������
		WriteToAD9959ViaSpi(CSR,1,ChannelSelectRegisterdata3,0); 
	}
	
	
	
  void AD9959_Setwavefrequency (double f)  	                       //�������Ƶ��
 { 
	 uchar ChannelFrequencyTuningWord1data[4];  
   uchar ChannelFunctionRegisterdata[3] = {0x00,0x23,0x35};        //��Ƶģʽʱѡ���������ҹ��ܣ�sine��
 	 uchar FunctionRegister1data[3] = {0xD0,0x00,0x00};  
	 
	 		
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ�����Ŀ����Ϊ��ʵ�������ҹ���
																													         //��û��Ҫ��ʱ���Բ����øüĴ���ͬ��Ҳ�������������
																													         //�Ĵ���8��9λ����������ȣ����ĸ���λ
   WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord1data);   //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord1data,1); //д��Ƶ�ʿ�����	
 }

  void AD9959_Setwavephase(double f,int p)													//�����λ����ɵ�
 {
	 uchar ChannelPhaseOffsetTuningWorddata[2];
	 uchar ChannelFrequencyTuningWorddata[4];
	 
   uchar ChannelFunctionRegisterdata[3] = {0x00,0x23,0x35};        //��Ƶģʽʱѡ���������ҹ��ܣ�sine��
   uchar FunctionRegister1data[3] = {0xD0,0x00,0x00};   
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	  //���ù��ܼĴ���
	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ�����Ŀ����Ϊ��ʵ�������ҹ���
	 
	 WrPhaseOffsetTuningWorddata(p,ChannelPhaseOffsetTuningWorddata); //������λת����
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWorddata,0); //д����λ������
  
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWorddata);  	  //����Ƶ��ת����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWorddata,1);		//д��Ƶ�ʿ�����
	 
	 
 }	
 
  void AD9959_Setwaveamplitute(double f,int a)                     //������ȿ��Զ������
 {
   uchar ChannelFrequencyTuningWorddata[4];
	 uchar ASRAmplituteWordata[3];
	 uchar AmplitudeControldata[3] = {0xff,0x17,0xff};               //�ֶ������������
	 uchar ChannelFunctionRegisterdata[3] = {0x00,0x23,0x35};        //��Ƶģʽʱѡ���������ҹ��ܣ�sine��
	 
   uchar FunctionRegister1data[3] = {0xD0,0x00,0x00}; 
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ�����Ŀ����Ϊ��ʵ�������ҹ���
	 WrAmplitudeTuningWorddata1(a,AmplitudeControldata,ASRAmplituteWordata) ;
	 WriteToAD9959ViaSpi(ACR,3,ASRAmplituteWordata,0);              //����������ȿ���ģʽ
	
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWorddata);   //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWorddata,1); //д��Ƶ��ת����
 }
 //���ö��׵���
 //////////////////////////////////////////////////////
  void AD9959_SetFremodulation2(double f1,double f2)
 {  
// 	 u8 a2 = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0x00,0x00}; 

   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ��� 	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

	   //������ʼƵ��S0��0x0A��

	 WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);   //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����
	 	
	  //������ֹƵ��E0��0x04��

   WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord1data,1);  //д��Ƶ�ʿ�����

 }

  void AD9959_SetPhamodulation2(double f,int p1,int p2)              //p1��ʼ��λ��p2��ֹ��λ
 {
// 	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[2];
	 uchar ChannelPhaseOffsetTuningWord1data[2];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x34};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//��������ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0x00,0x00}; 
// 	 uchar FunctionRegister1data[3] = {0xD0,0x54,0x00};    						//��������ʱ����з���RU/RDʱѡ��
																																			//PO���е�Ƶ��P2���з���RU/RD
// 	 uchar AmplitudeControldata[3] = {0xff,0x1f,0xff}; 								//����RU/RD
		 
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������
//    WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0);    					//���������RU/RDģʽ��ѡ��,��Ҫ�޸Ĺ��ܼĴ���FR1
	  //���õ�ַ0x05��CPOW0�� ����λ

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,0);	//д����λ������
	 //���õ�ַ0x0a��CW1�� ����λ

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,0);		//д����λ������
	// f=2000000;    //�������Ƶ��
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord1data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord1data,1);		//д��Ƶ�ʿ�����	
 }
 
  void AD9959_SetAM2(double f)
 { 
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelAmplitudeTuningWorddata[4]={0x1f,0x30,0x00,0x00}; //72mV
	 uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};  //500mV 
	 uchar FunctionRegister1data[3]={0xD0,0x00,0x00}; 
	
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���
	
	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��
   
   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWorddata,0);	 // ���÷��ȴ�С��S2��
																																		//�������Ƶ�ʴ�С
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
	 
 }
 
 /////////////////////////////////////////////////////////////////////
 
 //�Ľ׵���   CH0/1      
 //////////////////////////////////////////////////////////////////////
 void AD9959_SetFremodulation4(double f1,double f2,double f3,double f4)
 {
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0x01,0x00};  	 
  
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���


   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,1);  //д��Ƶ�ʿ�����
}
 void AD9959_SetPhamodulation4(double f,int p1,int p2,int p3,int p4)
 {
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//�ļ�����ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0x01,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������
	 
	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������
	
	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
 }
 void AD9959_SetAM4(double f)
 {
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0x8f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0x5f,0x30,0x00,0x00};
	 
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0x01,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}

/////////////////////////////////////////////////////////////////////////
//  �Ľ׵��� CH2/3    
/////////////////////////////////////////////////////////////////////////

void AD9959_SetFremodulation42(double f1,double f2,double f3,double f4)
 {
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0x51,0x00};  	 
  
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,1);  //д��Ƶ�ʿ�����
 }
 void AD9959_SetPhamodulation42(double f,int p1,int p2,int p3,int p4)
 {
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//�ļ�����ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0x51,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
 }
 void AD9959_SetAM42(double f)
 {
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0x8f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0x5f,0x30,0x00,0x00};
	 
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0x51,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}

/////////////////////////////////////////////////////////////////////////
//  �˽׵��� CH0  
/////////////////////////////////////////////////////////////////////////

void AD9959_SetFremodulation80(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xc2,0x00};  	 
 
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation80(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//�˼�����ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xc2,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������
	
	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM80(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0x5f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x3f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x1f,0x30,0x00,0x00};
	 
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xc2,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}
/////////////////////////////////////////////////////////////////////////
//  �˽׵��� CH1
/////////////////////////////////////////////////////////////////////////

void AD9959_SetFremodulation81(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xd2,0x00};  	 
 
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation81(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//�˼�����ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xd2,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM81(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0x5f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x3f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x1f,0x30,0x00,0x00};
	 
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xd2,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���
	 
	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}
/////////////////////////////////////////////////////////////////////////
//  �˽׵��� CH2    
/////////////////////////////////////////////////////////////////////////

void AD9959_SetFremodulation82(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xe2,0x00};  	 
 
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation82(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//�˼�����ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xe2,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM82(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0x5f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x3f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x1f,0x30,0x00,0x00};
	 
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xe2,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}

/////////////////////////////////////////////////////////////////////////
//  �˽׵��� CH3    
/////////////////////////////////////////////////////////////////////////

void AD9959_SetFremodulation83(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xf2,0x00};  	 

   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation83(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//�˼�����ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xf2,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM83(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0x5f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x3f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x1f,0x30,0x00,0x00};
	 
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xf2,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}


/////////////////////////////////////////////////////////////////////////
//  ʮ���׵��� CH0   
/////////////////////////////////////////////////////////////////////////
void AD9959_SetFremodulation160(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8,double f9,double f10,double f11,double f12,double f13,double f14,double f15,double f16)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFrequencyTuningWord8data[4];
	 uchar ChannelFrequencyTuningWord9data[4];
	 uchar ChannelFrequencyTuningWord10data[4];
	 uchar ChannelFrequencyTuningWord11data[4];
	 uchar ChannelFrequencyTuningWord12data[4];
	 uchar ChannelFrequencyTuningWord13data[4];
	 uchar ChannelFrequencyTuningWord14data[4];
	 uchar ChannelFrequencyTuningWord15data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xc3,0x00};  	 
  
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f9,ChannelFrequencyTuningWord8data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x11,4,ChannelFrequencyTuningWord8data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f10,ChannelFrequencyTuningWord9data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x12,4,ChannelFrequencyTuningWord9data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f11,ChannelFrequencyTuningWord10data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x13,4,ChannelFrequencyTuningWord10data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f12,ChannelFrequencyTuningWord11data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x14,4,ChannelFrequencyTuningWord11data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f13,ChannelFrequencyTuningWord12data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x15,4,ChannelFrequencyTuningWord12data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f14,ChannelFrequencyTuningWord13data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x16,4,ChannelFrequencyTuningWord13data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f15,ChannelFrequencyTuningWord14data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x017,4,ChannelFrequencyTuningWord14data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f16,ChannelFrequencyTuningWord15data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x18,4,ChannelFrequencyTuningWord15data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation160(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9,int p10,int p11,int p12,int p13,int p14,int p15,int p16)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 uchar ChannelPhaseOffsetTuningWord8data[4];
	 uchar ChannelPhaseOffsetTuningWord9data[4];
	 uchar ChannelPhaseOffsetTuningWord10data[4];
	 uchar ChannelPhaseOffsetTuningWord11data[4];
	 uchar ChannelPhaseOffsetTuningWord12data[4];
	 uchar ChannelPhaseOffsetTuningWord13data[4];
	 uchar ChannelPhaseOffsetTuningWord14data[4];
	 uchar ChannelPhaseOffsetTuningWord15data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//ʮ��������ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xc3,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p9,ChannelPhaseOffsetTuningWord8data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x11,4,ChannelPhaseOffsetTuningWord8data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p10,ChannelPhaseOffsetTuningWord9data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x12,4,ChannelPhaseOffsetTuningWord9data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p11,ChannelPhaseOffsetTuningWord10data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x13,4,ChannelPhaseOffsetTuningWord10data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p12,ChannelPhaseOffsetTuningWord11data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x14,4,ChannelPhaseOffsetTuningWord11data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p13,ChannelPhaseOffsetTuningWord12data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x15,4,ChannelPhaseOffsetTuningWord12data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p14,ChannelPhaseOffsetTuningWord13data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x16,4,ChannelPhaseOffsetTuningWord13data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p15,ChannelPhaseOffsetTuningWord14data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x17,4,ChannelPhaseOffsetTuningWord14data,1);	//д����λ������
	
	 WrPhaseOffsetTuningWorddata(p16,ChannelPhaseOffsetTuningWord15data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x18,4,ChannelPhaseOffsetTuningWord15data,1);		//д����λ������
	 
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM160(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xef,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0xcf,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0xaf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x8f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord8data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord9data[4]={0x6f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord10data[4]={0x5f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord11data[4]={0x4f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord12data[4]={0x3f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord13data[4]={0x2f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord14data[4]={0x1f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord15data[4]={0x0f,0x30,0x00,0x00};
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xc3,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);

	 WriteToAD9959ViaSpi(0x11,4,ChannelAmplitudeTuningWord8data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x12,4,ChannelAmplitudeTuningWord9data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x13,4,ChannelAmplitudeTuningWord10data,0);

	 WriteToAD9959ViaSpi(0x14,4,ChannelAmplitudeTuningWord11data,0);

	 WriteToAD9959ViaSpi(0x15,4,ChannelAmplitudeTuningWord12data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x16,4,ChannelAmplitudeTuningWord13data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x17,4,ChannelAmplitudeTuningWord14data,0);

	 WriteToAD9959ViaSpi(0x18,4,ChannelAmplitudeTuningWord15data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}
/////////////////////////////////////////////////////////////////////////
//  ʮ���׵��� CH1  
/////////////////////////////////////////////////////////////////////////
void AD9959_SetFremodulation161(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8,double f9,double f10,double f11,double f12,double f13,double f14,double f15,double f16)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFrequencyTuningWord8data[4];
	 uchar ChannelFrequencyTuningWord9data[4];
	 uchar ChannelFrequencyTuningWord10data[4];
	 uchar ChannelFrequencyTuningWord11data[4];
	 uchar ChannelFrequencyTuningWord12data[4];
	 uchar ChannelFrequencyTuningWord13data[4];
	 uchar ChannelFrequencyTuningWord14data[4];
	 uchar ChannelFrequencyTuningWord15data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xd3,0x00};  	 
 
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f9,ChannelFrequencyTuningWord8data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x11,4,ChannelFrequencyTuningWord8data,0);  //д��Ƶ�ʿ�����
	 
	 WrFrequencyTuningWorddata(f10,ChannelFrequencyTuningWord9data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x12,4,ChannelFrequencyTuningWord9data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f11,ChannelFrequencyTuningWord10data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x13,4,ChannelFrequencyTuningWord10data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f12,ChannelFrequencyTuningWord11data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x14,4,ChannelFrequencyTuningWord11data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f13,ChannelFrequencyTuningWord12data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x15,4,ChannelFrequencyTuningWord12data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f14,ChannelFrequencyTuningWord13data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x16,4,ChannelFrequencyTuningWord13data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f15,ChannelFrequencyTuningWord14data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x017,4,ChannelFrequencyTuningWord14data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f16,ChannelFrequencyTuningWord15data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x18,4,ChannelFrequencyTuningWord15data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation161(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9,int p10,int p11,int p12,int p13,int p14,int p15,int p16)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 uchar ChannelPhaseOffsetTuningWord8data[4];
	 uchar ChannelPhaseOffsetTuningWord9data[4];
	 uchar ChannelPhaseOffsetTuningWord10data[4];
	 uchar ChannelPhaseOffsetTuningWord11data[4];
	 uchar ChannelPhaseOffsetTuningWord12data[4];
	 uchar ChannelPhaseOffsetTuningWord13data[4];
	 uchar ChannelPhaseOffsetTuningWord14data[4];
	 uchar ChannelPhaseOffsetTuningWord15data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//ʮ��������ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xd3,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p9,ChannelPhaseOffsetTuningWord8data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x11,4,ChannelPhaseOffsetTuningWord8data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p10,ChannelPhaseOffsetTuningWord9data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x12,4,ChannelPhaseOffsetTuningWord9data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p11,ChannelPhaseOffsetTuningWord10data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x13,4,ChannelPhaseOffsetTuningWord10data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p12,ChannelPhaseOffsetTuningWord11data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x14,4,ChannelPhaseOffsetTuningWord11data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p13,ChannelPhaseOffsetTuningWord12data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x15,4,ChannelPhaseOffsetTuningWord12data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p14,ChannelPhaseOffsetTuningWord13data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x16,4,ChannelPhaseOffsetTuningWord13data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p15,ChannelPhaseOffsetTuningWord14data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x17,4,ChannelPhaseOffsetTuningWord14data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p16,ChannelPhaseOffsetTuningWord15data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x18,4,ChannelPhaseOffsetTuningWord15data,1);		//д����λ������
	 
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM161(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xef,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0xcf,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0xaf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x8f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord8data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord9data[4]={0x6f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord10data[4]={0x5f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord11data[4]={0x4f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord12data[4]={0x3f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord13data[4]={0x2f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord14data[4]={0x1f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord15data[4]={0x0f,0x30,0x00,0x00};
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xd3,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);

	 WriteToAD9959ViaSpi(0x11,4,ChannelAmplitudeTuningWord8data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x12,4,ChannelAmplitudeTuningWord9data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x13,4,ChannelAmplitudeTuningWord10data,0);

	 WriteToAD9959ViaSpi(0x14,4,ChannelAmplitudeTuningWord11data,0);

	 WriteToAD9959ViaSpi(0x15,4,ChannelAmplitudeTuningWord12data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x16,4,ChannelAmplitudeTuningWord13data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x17,4,ChannelAmplitudeTuningWord14data,0);

	 WriteToAD9959ViaSpi(0x18,4,ChannelAmplitudeTuningWord15data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}

/////////////////////////////////////////////////////////////////////////
//  ʮ���׵��� CH2 
/////////////////////////////////////////////////////////////////////////
void AD9959_SetFremodulation162(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8,double f9,double f10,double f11,double f12,double f13,double f14,double f15,double f16)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFrequencyTuningWord8data[4];
	 uchar ChannelFrequencyTuningWord9data[4];
	 uchar ChannelFrequencyTuningWord10data[4];
	 uchar ChannelFrequencyTuningWord11data[4];
	 uchar ChannelFrequencyTuningWord12data[4];
	 uchar ChannelFrequencyTuningWord13data[4];
	 uchar ChannelFrequencyTuningWord14data[4];
	 uchar ChannelFrequencyTuningWord15data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xe3,0x00};  	 
  
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f9,ChannelFrequencyTuningWord8data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x11,4,ChannelFrequencyTuningWord8data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f10,ChannelFrequencyTuningWord9data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x12,4,ChannelFrequencyTuningWord9data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f11,ChannelFrequencyTuningWord10data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x13,4,ChannelFrequencyTuningWord10data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f12,ChannelFrequencyTuningWord11data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x14,4,ChannelFrequencyTuningWord11data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f13,ChannelFrequencyTuningWord12data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x15,4,ChannelFrequencyTuningWord12data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f14,ChannelFrequencyTuningWord13data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x16,4,ChannelFrequencyTuningWord13data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f15,ChannelFrequencyTuningWord14data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x017,4,ChannelFrequencyTuningWord14data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f16,ChannelFrequencyTuningWord15data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x18,4,ChannelFrequencyTuningWord15data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation162(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9,int p10,int p11,int p12,int p13,int p14,int p15,int p16)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 uchar ChannelPhaseOffsetTuningWord8data[4];
	 uchar ChannelPhaseOffsetTuningWord9data[4];
	 uchar ChannelPhaseOffsetTuningWord10data[4];
	 uchar ChannelPhaseOffsetTuningWord11data[4];
	 uchar ChannelPhaseOffsetTuningWord12data[4];
	 uchar ChannelPhaseOffsetTuningWord13data[4];
	 uchar ChannelPhaseOffsetTuningWord14data[4];
	 uchar ChannelPhaseOffsetTuningWord15data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//ʮ��������ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xe3,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������
	
	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������
	
	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p9,ChannelPhaseOffsetTuningWord8data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x11,4,ChannelPhaseOffsetTuningWord8data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p10,ChannelPhaseOffsetTuningWord9data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x12,4,ChannelPhaseOffsetTuningWord9data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p11,ChannelPhaseOffsetTuningWord10data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x13,4,ChannelPhaseOffsetTuningWord10data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p12,ChannelPhaseOffsetTuningWord11data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x14,4,ChannelPhaseOffsetTuningWord11data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p13,ChannelPhaseOffsetTuningWord12data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x15,4,ChannelPhaseOffsetTuningWord12data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p14,ChannelPhaseOffsetTuningWord13data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x16,4,ChannelPhaseOffsetTuningWord13data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p15,ChannelPhaseOffsetTuningWord14data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x17,4,ChannelPhaseOffsetTuningWord14data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p16,ChannelPhaseOffsetTuningWord15data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x18,4,ChannelPhaseOffsetTuningWord15data,1);		//д����λ������
	 
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM162(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xef,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0xcf,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0xaf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x8f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord8data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord9data[4]={0x6f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord10data[4]={0x5f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord11data[4]={0x4f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord12data[4]={0x3f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord13data[4]={0x2f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord14data[4]={0x1f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord15data[4]={0x0f,0x30,0x00,0x00};
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xe3,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);

	 WriteToAD9959ViaSpi(0x11,4,ChannelAmplitudeTuningWord8data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x12,4,ChannelAmplitudeTuningWord9data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x13,4,ChannelAmplitudeTuningWord10data,0);

	 WriteToAD9959ViaSpi(0x14,4,ChannelAmplitudeTuningWord11data,0);

	 WriteToAD9959ViaSpi(0x15,4,ChannelAmplitudeTuningWord12data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x16,4,ChannelAmplitudeTuningWord13data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x17,4,ChannelAmplitudeTuningWord14data,0);

	 WriteToAD9959ViaSpi(0x18,4,ChannelAmplitudeTuningWord15data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}




/////////////////////////////////////////////////////////////////////////
//  ʮ���׵��� CH3   
/////////////////////////////////////////////////////////////////////////

void AD9959_SetFremodulation163(double f1,double f2,double f3,double f4,double f5,double f6,double f7,double f8,double f9,double f10,double f11,double f12,double f13,double f14,double f15,double f16)
{
// 	 u8 a = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelFrequencyTuningWord1data[4];
	 uchar ChannelFrequencyTuningWord2data[4];
	 uchar ChannelFrequencyTuningWord3data[4];
	 uchar ChannelFrequencyTuningWord4data[4];
	 uchar ChannelFrequencyTuningWord5data[4];
	 uchar ChannelFrequencyTuningWord6data[4];
	 uchar ChannelFrequencyTuningWord7data[4];
	 uchar ChannelFrequencyTuningWord8data[4];
	 uchar ChannelFrequencyTuningWord9data[4];
	 uchar ChannelFrequencyTuningWord10data[4];
	 uchar ChannelFrequencyTuningWord11data[4];
	 uchar ChannelFrequencyTuningWord12data[4];
	 uchar ChannelFrequencyTuningWord13data[4];
	 uchar ChannelFrequencyTuningWord14data[4];
	 uchar ChannelFrequencyTuningWord15data[4];
	 uchar ChannelFunctionRegisterdata[3] = {0x80,0x23,0x30};        //��RU/RD
	 uchar FunctionRegister1data[3] = {0xD0,0xf3,0x00};  	 
  
   WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���	 
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);       //����ͨ�����ܼĴ���

   WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWord0data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x04,4,ChannelFrequencyTuningWord0data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWord1data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWord1data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f3,ChannelFrequencyTuningWord2data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0B,4,ChannelFrequencyTuningWord2data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f4,ChannelFrequencyTuningWord3data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0C,4,ChannelFrequencyTuningWord3data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f5,ChannelFrequencyTuningWord4data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0D,4,ChannelFrequencyTuningWord4data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f6,ChannelFrequencyTuningWord5data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0E,4,ChannelFrequencyTuningWord5data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f7,ChannelFrequencyTuningWord6data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x0F,4,ChannelFrequencyTuningWord6data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f8,ChannelFrequencyTuningWord7data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x10,4,ChannelFrequencyTuningWord7data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f9,ChannelFrequencyTuningWord8data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x11,4,ChannelFrequencyTuningWord8data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f10,ChannelFrequencyTuningWord9data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x12,4,ChannelFrequencyTuningWord9data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f11,ChannelFrequencyTuningWord10data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x13,4,ChannelFrequencyTuningWord10data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f12,ChannelFrequencyTuningWord11data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x14,4,ChannelFrequencyTuningWord11data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f13,ChannelFrequencyTuningWord12data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x15,4,ChannelFrequencyTuningWord12data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f14,ChannelFrequencyTuningWord13data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x16,4,ChannelFrequencyTuningWord13data,0);  //д��Ƶ�ʿ�����

	 WrFrequencyTuningWorddata(f15,ChannelFrequencyTuningWord14data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x017,4,ChannelFrequencyTuningWord14data,0);  //д��Ƶ�ʿ�����

   WrFrequencyTuningWorddata(f16,ChannelFrequencyTuningWord15data);    //��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(0x18,4,ChannelFrequencyTuningWord15data,1);  //д��Ƶ�ʿ�����
}
void AD9959_SetPhamodulation163(double f,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9,int p10,int p11,int p12,int p13,int p14,int p15,int p16)
{
// 	 u8 b = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord0data[4];
	 uchar ChannelPhaseOffsetTuningWord1data[4];
	 uchar ChannelPhaseOffsetTuningWord2data[4];
	 uchar ChannelPhaseOffsetTuningWord3data[4];
	 uchar ChannelPhaseOffsetTuningWord4data[4];
	 uchar ChannelPhaseOffsetTuningWord5data[4];
	 uchar ChannelPhaseOffsetTuningWord6data[4];
	 uchar ChannelPhaseOffsetTuningWord7data[4];
	 uchar ChannelPhaseOffsetTuningWord8data[4];
	 uchar ChannelPhaseOffsetTuningWord9data[4];
	 uchar ChannelPhaseOffsetTuningWord10data[4];
	 uchar ChannelPhaseOffsetTuningWord11data[4];
	 uchar ChannelPhaseOffsetTuningWord12data[4];
	 uchar ChannelPhaseOffsetTuningWord13data[4];
	 uchar ChannelPhaseOffsetTuningWord14data[4];
	 uchar ChannelPhaseOffsetTuningWord15data[4];
	 
	 uchar ChannelFunctionRegisterdata[3] = {0xc0,0x03,0x30};  					//��λ����ģʽ���ã�����ɨ����ܿ�����
	 uchar AmplitudeControldata[3] = {0x00,0x03,0xff};									//ʮ��������ʱ���ã�Ĭ��������
	 uchar FunctionRegister1data[3] = {0xD0,0xf3,0x00}; 

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 		  //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);    			//����ͨ�����ܼĴ���������λ��������

	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWord0data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWord0data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWord1data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWord1data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p3,ChannelPhaseOffsetTuningWord2data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0b,4,ChannelPhaseOffsetTuningWord2data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p4,ChannelPhaseOffsetTuningWord3data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0c,4,ChannelPhaseOffsetTuningWord3data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p5,ChannelPhaseOffsetTuningWord4data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0d,4,ChannelPhaseOffsetTuningWord4data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p6,ChannelPhaseOffsetTuningWord5data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x0e,4,ChannelPhaseOffsetTuningWord5data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p7,ChannelPhaseOffsetTuningWord6data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x0f,4,ChannelPhaseOffsetTuningWord6data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p8,ChannelPhaseOffsetTuningWord7data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x10,4,ChannelPhaseOffsetTuningWord7data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p9,ChannelPhaseOffsetTuningWord8data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x11,4,ChannelPhaseOffsetTuningWord8data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p10,ChannelPhaseOffsetTuningWord9data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x12,4,ChannelPhaseOffsetTuningWord9data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p11,ChannelPhaseOffsetTuningWord10data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x13,4,ChannelPhaseOffsetTuningWord10data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p12,ChannelPhaseOffsetTuningWord11data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x14,4,ChannelPhaseOffsetTuningWord11data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p13,ChannelPhaseOffsetTuningWord12data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x15,4,ChannelPhaseOffsetTuningWord12data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p14,ChannelPhaseOffsetTuningWord13data); //��ʮ������λ��ת��Ϊ2������λ�������
	 WriteToAD9959ViaSpi(0x16,4,ChannelPhaseOffsetTuningWord13data,1);		//д����λ������

	 WrPhaseOffsetTuningWorddata(p15,ChannelPhaseOffsetTuningWord14data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x17,4,ChannelPhaseOffsetTuningWord14data,1);	//д����λ������

	 WrPhaseOffsetTuningWorddata(p16,ChannelPhaseOffsetTuningWord15data); //��ʮ������λ��ת��Ϊ2������λ������
	 WriteToAD9959ViaSpi(0x18,4,ChannelPhaseOffsetTuningWord15data,1);		//д����λ������
	 
	 f=200000;
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);    	//��ʮ����Ƶ����ת��Ϊ2����Ƶ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);		//д��Ƶ�ʿ�����
}
void AD9959_SetAM163(double f)
{
// 	 u8 cn = 0;
	 uchar ChannelFrequencyTuningWord0data[4];
	
	 uchar AmplitudeControldata[3]={0x00,0x03,0xff};
	 uchar ChannelAmplitudeTuningWord1data[4]={0xef,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord2data[4]={0xdf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord3data[4]={0xcf,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord4data[4]={0xbf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord5data[4]={0xaf,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord6data[4]={0x9f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord7data[4]={0x8f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord8data[4]={0x7f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord9data[4]={0x6f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord10data[4]={0x5f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord11data[4]={0x4f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord12data[4]={0x3f,0x30,0x00,0x00};
	 uchar ChannelAmplitudeTuningWord13data[4]={0x2f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord14data[4]={0x1f,0x30,0x00,0x00};
   uchar ChannelAmplitudeTuningWord15data[4]={0x0f,0x30,0x00,0x00};
   uchar ChannelFunctionRegisterdata[3] = {0x40,0x03,0x30};
	 uchar FunctionRegister1data[3]={0xD0,0xf3,0x00};

	 WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	 //���ù��ܼĴ���
	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0); 			 //����ͨ�����ܼĴ���

	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWord1data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0b,4,ChannelAmplitudeTuningWord2data,0);

	 WriteToAD9959ViaSpi(0x0c,4,ChannelAmplitudeTuningWord3data,0);

	 WriteToAD9959ViaSpi(0x0d,4,ChannelAmplitudeTuningWord4data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x0e,4,ChannelAmplitudeTuningWord5data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x0f,4,ChannelAmplitudeTuningWord6data,0);

	 WriteToAD9959ViaSpi(0x10,4,ChannelAmplitudeTuningWord7data,0);

	 WriteToAD9959ViaSpi(0x11,4,ChannelAmplitudeTuningWord8data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x12,4,ChannelAmplitudeTuningWord9data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x13,4,ChannelAmplitudeTuningWord10data,0);

	 WriteToAD9959ViaSpi(0x14,4,ChannelAmplitudeTuningWord11data,0);

	 WriteToAD9959ViaSpi(0x15,4,ChannelAmplitudeTuningWord12data,0); 						 //���÷��ȴ�С��S1��

   WriteToAD9959ViaSpi(0x16,4,ChannelAmplitudeTuningWord13data,0);	 // ���÷��ȴ�С��S2��

	 WriteToAD9959ViaSpi(0x17,4,ChannelAmplitudeTuningWord14data,0);

	 WriteToAD9959ViaSpi(0x18,4,ChannelAmplitudeTuningWord15data,0);
	 
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data);   	//дƵ�ʿ�����
   WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);
}

/////////////////////////////////////////////////////////////////////////
 void AD9959_Frequency_Sweep(double f1,double f2,double a1,double a2) //f1��ʼƵ�ʣ�f2��ֹƵ�ʣ�a1�����ģ�a2�½���
{ 
	uchar ChannelFrequencyTuningWorddata1[4];
  uchar ChannelFrequencyTuningWorddata2[4];
  uchar ChannelFrequencyTuningWorddata3[4];
  uchar ChannelFrequencyTuningWorddata4[4];
	uchar FunctionRegister1data[3] = {0xD0,0x00,0x00};    							//Ĭ�������ѡ��   
	uchar ChannelFunctionRegisterdata[3] = {0x80,0x43,0x20};						//ɨƵģʽʱѡ��;����ɨ��û�����ã���RU/RD
  uchar SweepRampRatedata[2] = {0xff,0xff};														//Ĭ�ϵ�λɨ��ʱ���
//uchar FunctionRegister1data[3] = {0xD0,0x04,0x00};    							//����ɨ��ʱ��ҪRU/RDʱѡ���� 
// uchar AmplitudeControldata[3] = {0xff,0x1f,0xff};									//����RU/RD
	
  WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);        		 	 	  //���ù��ܼĴ���
  WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);  					//  ����ͨ�����ܼĴ���
// 	WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,1); 								//���������RU/RDģʽ��ѡ��,��Ҫ�޸Ĺ��ܼĴ���FR1
// 	f=500000;    // ������ʼƵ��S0��0x04��
  
	
	WrFrequencyTuningWorddata(f1,ChannelFrequencyTuningWorddata1);   		//дƵ�ʿ�����
	WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWorddata1,0);
// 	f=5000000; //������ֹƵ��(0x0A)
 
  WrFrequencyTuningWorddata(f2,ChannelFrequencyTuningWorddata2);  	 //дƵ�ʿ�����
  WriteToAD9959ViaSpi(0x0A,4,ChannelFrequencyTuningWorddata2,0); 
// 	f=100;   //����������
		
	WrFrequencyTuningWorddata(a1,ChannelFrequencyTuningWorddata3);   	 //дƵ�ʿ�����
	WriteToAD9959ViaSpi(RDW,4,ChannelFrequencyTuningWorddata3,0);
	
//   f=100;  //�����½���
	WrFrequencyTuningWorddata(a2,ChannelFrequencyTuningWorddata4);   	 //дƵ�ʿ�����
	WriteToAD9959ViaSpi(FDW,4,ChannelFrequencyTuningWorddata4,0);
		
  WriteToAD9959ViaSpi(SRR,2,SweepRampRatedata,1);										 //���õ�λ����ʱ��	
 
}
 
 void AD9959_Phase_Sweep(int p1,int p2,int a1,int a2,double f)       //p1��ʼ��λ��p2��ֹ��λ��a1���������ģ�a2�����½���
{
	uchar ChannelPhaseOffsetTuningWorddata1[2];
	uchar ChannelPhaseOffsetTuningWorddata2[2];
	uchar ChannelPhaseOffsetTuningWorddata3[2];
	uchar ChannelPhaseOffsetTuningWorddata4[2];
	uchar ChannelFrequencyTuningWord0data[4];
	
	uchar FunctionRegister1data[3] = {0xD0,0x00,0x00};   							 //Ĭ�������ѡ��   
	uchar ChannelFunctionRegisterdata[3] = {0xc0,0xC3,0x30};					 //ɨ��ģʽʱѡ������ɨ��û�����ã���RU/RD
  uchar SweepRampRatedata[2] = {0xff,0xff};													 //Ĭ�ϵ�λɨ��ʱ���
//uchar FunctionRegister1data[3] = {0xD0,0x04,0x00};    						 //����ɨ��ʱ��ҪRU/RDʱѡ���� 
// uchar AmplitudeControldata[3] = {0xff,0x1f,0xff};								 //����RU/RD

	WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         		 	 //���ù��ܼĴ���
 	 WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);				 //  ����ͨ�����ܼĴ���
// 	 WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,1); 						 //���������RU/RDģʽ��ѡ��,��Ҫ�޸Ĺ��ܼĴ���FR1
// 	 p=0;// ������ʼ��λS0��0x04��   �����������Ӻ������治һ��
	 WrPhaseOffsetTuningWorddata(p1,ChannelPhaseOffsetTuningWorddata1);
	 WriteToAD9959ViaSpi(CPOW0,2,ChannelPhaseOffsetTuningWorddata1,0);
//    p=360;//������ֹ��λE0(0x0A)
	 WrPhaseOffsetTuningWorddata(p2,ChannelPhaseOffsetTuningWorddata2);
	 WriteToAD9959ViaSpi(0x0a,4,ChannelPhaseOffsetTuningWorddata2,0);
//    p=10;//����������
	 WrPhaseOffsetTuningWorddata(a1,ChannelPhaseOffsetTuningWorddata3);
	 WriteToAD9959ViaSpi(RDW,4,ChannelPhaseOffsetTuningWorddata3,0);
//    p=10;//�����½���
	 WrPhaseOffsetTuningWorddata(a2,ChannelPhaseOffsetTuningWorddata4);
	 WriteToAD9959ViaSpi(FDW,4,ChannelPhaseOffsetTuningWorddata4,0);
	 WriteToAD9959ViaSpi(SRR,2,SweepRampRatedata,0);										//д��λ����ʱ��
// 	 f=400000;    //�������Ƶ�ʴ�С
	 WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWord0data); 		  //дƵ�ʿ�����
	 WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWord0data,1);

}

void AD9959_Amplitute_Sweep(int a,int a1,int a2,double f)   					//a��ֹ���ȣ�a1�����ģ�a2�½��ģ�f���Ƶ��
{
	uchar ChannelAmplitudeTuningWorddata1[4];
	uchar ChannelAmplitudeTuningWorddata2[4];
	uchar ChannelAmplitudeTuningWorddata3[4];
	uchar ChannelFrequencyTuningWorddata4[4];
	
	uchar FunctionRegister1data[3] = {0xD0,0x00,0x00};    						//Ĭ�������ѡ��   
	uchar ChannelFunctionRegisterdata[3] = {0x40,0x43,0x20};					//����ɨ��λ����
  uchar AmplitudeControldata[3] = {0x00,0x0,0x3f};  								//����ɨ��ģʽʱ����
  uchar SweepRampRatedata[2] = {0xff,0xff};													//Ĭ�ϵ�λɨ��ʱ���

  WriteToAD9959ViaSpi(FR1,3,FunctionRegister1data,0);         	 	  //���ù��ܼĴ���
	WriteToAD9959ViaSpi(CFR,3,ChannelFunctionRegisterdata,0);
	//д��ʼ����S0
  WriteToAD9959ViaSpi(ACR,3,AmplitudeControldata,0);
	//д��ֹ����E0
// 	a=1023; //д������,����д��1024�����Ϊ1023
	WrAmplitudeTuningWorddata(a,ChannelAmplitudeTuningWorddata1);
  WriteToAD9959ViaSpi(0x0a,4,ChannelAmplitudeTuningWorddata1,0); 		//CTW0 address 0x04.���10MHZƵ��
// 	a=10; //д������
	WrAmplitudeTuningWorddata(a1,ChannelAmplitudeTuningWorddata2);    //дƵ�ʿ�����
	WriteToAD9959ViaSpi(RDW,4,ChannelAmplitudeTuningWorddata2,0);
//   a=10;  //д�½���
	WrAmplitudeTuningWorddata(a2,ChannelAmplitudeTuningWorddata3);    //дƵ�ʿ�����
	WriteToAD9959ViaSpi(FDW,4,ChannelAmplitudeTuningWorddata3,0);
 	WriteToAD9959ViaSpi(SRR,2,SweepRampRatedata,0);										//д��λ����ʱ��
// 	f=400000;    
	WrFrequencyTuningWorddata(f,ChannelFrequencyTuningWorddata4);   	//дƵ�ʿ�����
  WriteToAD9959ViaSpi(CFTW0,4,ChannelFrequencyTuningWorddata4,1);
	
}


