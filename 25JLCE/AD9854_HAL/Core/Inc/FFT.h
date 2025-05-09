#ifndef __FFT_H
#define __FFT_H

#include "main.h"
#include "string.h"
#include "stdlib.h"
#include "errno.h"
#include "arm_math.h"

#define FFT_LENGTH 1024

float find_dominant_frequency(uint16_t* adc_data, float fs, uint16_t type);

#endif