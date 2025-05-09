#include "FFT.h"

float fft_inputbuf[FFT_LENGTH * 2];
float fft_outputbuf[FFT_LENGTH];
float Phase_Result[FFT_LENGTH];

float thrid_output_F = 0;

float thrid_output_A = 0;

arm_cfft_radix4_instance_f32 scfft;  // FFT 实例

float find_dominant_frequency(uint16_t* adc_data, float fs,uint16_t type) {
    // 1. 转换 ADC 数据为浮点数
    for (int i = 0; i < FFT_LENGTH; i++) {
        fft_inputbuf[2 * i] = (float)adc_data[i];
        fft_inputbuf[2 * i + 1] = 0;
    }

    // 2. 执行 FFT
    arm_cfft_radix4_init_f32(&scfft, FFT_LENGTH, 0, 1);
    arm_cfft_radix4_f32(&scfft, fft_inputbuf);
    arm_cmplx_mag_f32(fft_inputbuf, fft_outputbuf, FFT_LENGTH);

    // 3. 找主频
    float max_mag = 0;
    uint16_t max_idx = 0;
    for (int i = 1; i < FFT_LENGTH / 2; i++) {  // 忽略直流分量（i=0）
        if (fft_outputbuf[i] > max_mag) {
            max_mag = fft_outputbuf[i];
            max_idx = i;
        }
    }

    float dominant_freq = (max_idx * fs) / FFT_LENGTH;

    if (type == 1) {
        thrid_output_F = fft_outputbuf[max_idx * 3]*1.f / fft_outputbuf[max_idx]*1.f;  // 更新全局变量
    } else if (type == 2) {
        thrid_output_A = fft_outputbuf[max_idx * 3]*1.f / fft_outputbuf[max_idx]*1.f;  // 更新全局变量
    }
    // printf("Dominant Frequency: %.2f Hz (Magnitude: %.2f)\r\n", dominant_freq, max_mag);
    return dominant_freq;
}