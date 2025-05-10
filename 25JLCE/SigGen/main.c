#include <visa.h>
#include <stdio.h>
#include "DG4202.h"
#include "Windows.h"
#include "serial.h"

// 打开一个data.txt文件
// 以追加模式打开，写一个函数用于在最后一行写入数据
FILE *file;
const char *filename = "data.txt";

// Serial Port Variables
PORT com_port;
char buff[1024] = {0};
int rcv_len = 0;
char* str_invitation = "T";

void FM_sweep_for_data_collect()
{
    Set_FM(1); // 启用调频
    for (int f = 1000; f <= 10000; f += 200)
    {
        for (int m = 1; m<=5; m++)
        {
            memset(buff, 0, 1024);
            Set_FM_frequency(f);
            Set_FM_deviation(m * f);
            Sleep(3000); // 等待4秒
            printf("send data %s\n", str_invitation);
            SendData(com_port, str_invitation); // 发送数据
            Sleep(50); // 等待50ms

            rcv_len = Serial_ReciveData(com_port, buff, 1024);
            if (buff[0] == '0') {
                m-=1;
                continue;
            }
            if (rcv_len > 0) {
                printf("%s\n", buff);
            }

            // printf("Record data %s\n", buff);
            fprintf(file, "(%d,%d,%s),\n", f, m, buff); // 写入数据并换行
            Sleep(500); // 等待0.5秒
        }
    }
}

void FSK_sweep_for_data_collect(int carrier_freq_Hz)
{
    Set_FSK(1); // 启用FSK
    Set_FSK_Polarity(1); // 设置FSK极性为正
    for (int f = 1000; f <= 5000; f += 1000) // 码率=2*f bps, 可为2、4、6、8、10kbps
    {
        for (int h = 2; h<=5; h++)
        {
            memset(buff, 0, 1024);
            Set_FSK_frequency(carrier_freq_Hz+h*f); // 设置fc1
            Set_FSK_Rate(f); // 设置FSK码率
            Sleep(3000); // 等待4秒
            printf("send data %s\n", str_invitation);
            SendData(com_port, str_invitation); // 发送数据
            Sleep(50); // 等待50ms

            rcv_len = Serial_ReciveData(com_port, buff, 1024);
            if (buff[0] == '0') {
                h-=1;
                continue;
            }
            if (rcv_len > 0) {
                printf("%s\n", buff);
            }

            // printf("Record data %s\n", buff);
            fprintf(file, "(%d,%d,%s),\n", f, h, buff); // 写入数据并换行
            Sleep(500); // 等待0.5秒
        }
    }
}

void AM_sweep_for_data_collect(int carrier_freq_Hz){
    Set_AM(1); // 启用调幅
        for (int m = 10; m<=100; m+=10)
        {
            memset(buff, 0, 1024);
            Set_AM_depth(m);
            Sleep(3000); // 等待4秒
            printf("send data %s\n", str_invitation);
            SendData(com_port, str_invitation); // 发送数据
            Sleep(50); // 等待50ms

            rcv_len = Serial_ReciveData(com_port, buff, 1024);
            if (rcv_len > 10 || buff[0] == '-') {
                m-=10;
                continue;
            }
            if (rcv_len > 0) {
                printf("%s\n", buff);
            }

            // printf("Record data %s\n", buff);
            fprintf(file, "(%d,%d,%s),\n", carrier_freq_Hz, m, buff); // 写入数据并换行
            Sleep(500); // 等待0.5秒
        }
    Set_AM(0); // 关闭调幅
}

void FM_sweep_for_data_collect_TEST()
{
    Set_FM(1); // 启用调频
    Channel1_ON(); // 打开通道1
    for (int f = 1000; f <= 10000; f += 1000)
    {
        for (int m = 1; m<=5; m++)
        {
            Set_FM_frequency(f);
            Set_FM_deviation(m * f);
            Sleep(3000); // 等待4秒
        }
    }
}

int main()
{
    int f_carrier = 10000000; // 载波频率5MHz
    int FM_fdiv = 6000; // FM频偏
    int FM_f_source = 5000; // FM源频率
    int m_f = 1; // 调频系数
    double amplitude = 0.05; // 幅度50mVpp

    // Set Serial Port
    com_port = serial_init(16, 115200, 8, 1, 0);

    // Open File
    file = fopen(filename, "a"); // 以追加模式打开文件
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    
    // fprintf(file, "HEADER\n"); // 写入文件头

    DG4202_Init();
    Set_frequency(f_carrier);
    Set_amplitude(amplitude);
    Set_waveform(SINE);
    Channel1_ON(); // 打开通道1

    // //AM TEST
    // Set_AM(1); // 启用调幅
    // Set_AM_frequency(10000); // 设置调幅源频率
    // Set_AM_depth(100); // 设置调幅深度
    // //ENDOF AM TEST
    
    // Set_FM(1); // 启用调频
    // Set_FM_frequency(FM_f_source); // 设置调频源频率
    // Set_FM_deviation(FM_fdiv); // 设置调频频偏

    //FM_sweep_for_data_collect(); // 调频频率和偏差的扫频数据采集
    // FSK_sweep_for_data_collect(f_carrier); // FSK频率和码率的扫频数据采集
    // for (int i = 1; i <= 10; i+=3){
    //     Set_frequency(i*1000000);
    //     AM_sweep_for_data_collect(i);
    // }
    for (int i = 10; i <= 20; i+=1){
        Set_frequency(i*1000000);
        AM_sweep_for_data_collect(i);
    }
    
    

    // for (int f = 1000; f <= 10000; f += 1000)
    // {
    //     for (int m = 1; m<=5; m++)
    //     {
    //         memset(buff, 0, 1024);
    //         Set_FM_frequency(f);
    //         Set_FM_deviation(m * f);
    //         Sleep(3000); // 等待4秒
    //         printf("send data %s\n", str_invitation);
    //         SendData(com_port, str_invitation); // 发送数据
    //         Sleep(50); // 等待50ms

    //         rcv_len = Serial_ReciveData(com_port, buff, 1024);
    //         if (rcv_len > 0) {
    //             printf("%s\n", buff);
    //         }

    //         // printf("Record data %s\n", buff);
    //         fprintf(file, "(%d,%d,%s),\n", f, m, buff); // 写入数据并换行
    //         Sleep(500); // 等待0.5秒
    //     }
    // }

    // 发送SCPI命令（例如设置正弦波输出）
    // viPrintf(instrument, "SOUR1:FUNC SIN\n");  // CH1输出正弦波
    // viPrintf(instrument, "SOUR1:FREQ 1000\n"); // 设置频率1kHz
    // viPrintf(instrument, "SOUR1:VOLT 1\n");    // 设置幅度1Vpp

    // 打开仪器的MOD模式
    // viPrintf(instrument, "OUTP1:MOD ON\n"); // 打开CH1的MOD模式

    // // 设置输出1MHz 50mVpp的正弦波
    // viPrintf(instrument, "SOURce1:FUNCTION SINe\n");
    // viPrintf(instrument, "SOURce1:FREQuency %d\n", f_carrier);
    // viPrintf(instrument, "SOURce1:VOLTage:AMPLitude 0.05\n");
    

    // // 启用FM, 设置频偏为5kHz
    // viPrintf(instrument, "SOURce1:FM:SOUR INT\n");
    // viPrintf(instrument, "SOURce1:FM:INTernal:FREQuency 1E4\n");
    // // 设置调制源频率为1kHz
    // viPrintf(instrument, "SOURce1:FM:INTernal:FREQuency %d\n", FM_f_source);
    // // 设置频偏为FM_fdiv
    // viPrintf(instrument, "SOURce1:FM:DEV %d\n", FM_fdiv);
    // viPrintf(instrument, "SOURce1:FM:STATe ON\n");


    // 打开通道1
    // viPrintf(instrument, "OUTPut1:STATe ON\n");


    DG4202_Disconnect();
    printf("DG4202 Disconnected (Device ID: %s)\n", DG4202_ReadID());

    fclose(file); // 关闭文件
    return 0;
}