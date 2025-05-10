/**
 ******************************************************************************
 * @file    DG4202.c
 * @author  AISuck Huang
 * @brief   DG4202 function generator driver.
 *          Based on the VISA library, SCPI commands are used to control the instrument.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "DG4202.h"
#include <stdio.h>

// DG4202 Instrument Variables
ViSession defaultRM, instrument;
ViStatus status;
char DG4202_buffer[256] = {0};

int DG4202_Init()
{
    // Initialize VISA Session
    status = viOpenDefaultRM(&defaultRM);
    if (status < VI_SUCCESS)
    {
        printf("VISA Initialization Failed\n");
        return -1;
    }

    // Open Instrument Connection
    status = viOpen(defaultRM, DG4202_NAME, VI_NULL, VI_NULL, &instrument);
    if (status < VI_SUCCESS)
    {
        printf("Cannot connect Instrument\n");
        viClose(defaultRM);
        return -1;
    }
    return 0;
}

char *DG4202_ReadID()
{
    // Read Instrument ID
    viQueryf(instrument, "*IDN?\n", "%t", DG4202_buffer);
    return DG4202_buffer;
}

int DG4202_Disconnect()
{
    // Disconnect Instrument
    viClose(instrument);
    viClose(defaultRM);
    return 0;
}

void Set_frequency(int frequency)
{
    // Set Frequency
    viPrintf(instrument, "SOURce1:FREQuency %d\n", frequency);
}
void Set_amplitude(double amplitude)
{
    // Set Amplitude
    viPrintf(instrument, "SOURce1:VOLTage:AMPLitude %f\n", amplitude);
}
void Set_waveform(int waveform)
{
    // Set Waveform Type
    switch (waveform)
    {
    case 0:
        viPrintf(instrument, "SOURce1:FUNCtion SINe\n");
        break;
    case 1:
        viPrintf(instrument, "SOURce1:FUNCtion SQUare\n");
        break;
    case 2:
        viPrintf(instrument, "SOURce1:FUNCtion RAMP\n");
        break;
    case 3:
        viPrintf(instrument, "SOURce1:FUNCtion PULSe\n");
        break;
    default:
        printf("Invalid waveform type\n");
        break;
    }
}
void Channel1_ON()
{
    // Enable Channel 1
    viPrintf(instrument, "OUTPut1:STATe ON\n");
}
void Set_FM(int mod_type)
{
    // Set FM modulation type
    switch (mod_type)
    {
    case 0:
        viPrintf(instrument, "SOURce1:FM:STATe OFF\n");
        break;
    case 1:
        viPrintf(instrument, "SOURce1:FM:STATe ON\n");
        break;
    default:
        printf("Invalid modulation type\n");
        break;
    }
}
void Set_FM_frequency(int frequency)
{
    // Set FM modulation frequency
    viPrintf(instrument, "SOURce1:FM:INTernal:FREQuency %d\n", frequency);
}
void Set_FM_deviation(int deviation)
{
    // Set FM deviation
    viPrintf(instrument, "SOURce1:FM:DEV %d\n", deviation);
}
void Set_AM(int mod_type)
{
    // Set AM modulation type
    switch (mod_type)
    {
    case 0:
        viPrintf(instrument, "SOURce1:AM:STATe OFF\n");
        break;
    case 1:
        viPrintf(instrument, "SOURce1:AM:STATe ON\n");
        break;
    default:
        printf("Invalid modulation type\n");
        break;
    }
}
void Set_AM_frequency(int frequency)
{
    // Set AM modulation frequency
    viPrintf(instrument, "SOURce1:AM:INTernal:FREQuency %d\n", frequency);
}
void Set_AM_depth(int depth_percent)
{
    // Set AM modulation depth (%)
    viPrintf(instrument, "SOURce1:AM:DEPTh %d\n", depth_percent);
}

void Set_FSK(int mod_type)
{
    // Set FSK modulation type
    switch (mod_type)
    {
    case 0:
        viPrintf(instrument, "SOURce1:FSKey:STATe OFF\n");
        break;
    case 1:
        viPrintf(instrument, "SOURce1:FSKey:STATe ON\n");
        break;
    default:
        printf("Invalid modulation type\n");
        break;
    }
}
void Set_FSK_frequency(int frequency_Hz)
{
    // Set FSK frequency
    viPrintf(instrument, "SOURce1:MOD:FSKey %d\n", frequency_Hz);
}
void Set_FSK_Rate(int rate_Hz)
{
    // Set FSK rate
    // Note: The rate is the frequency of the FSK signal, not the rate of change of the frequency.
    viPrintf(instrument, "SOURce1:MOD:FSKey:INTernal:RATE %d\n", rate_Hz);
}
void Set_FSK_Polarity(int positive)
{
    // Set FSK polarity
    switch (positive)
    {
    case 0:
        viPrintf(instrument, "SOURce1:MOD:FSKey:POLarity NEGative\n");
        break;
    case 1:
        viPrintf(instrument, "SOURce1:MOD:FSKey:POLarity POSitive\n");
        break;
    default:
        printf("Invalid polarity type\n");
        break;
    }
}

void Set_ASK(int mod_type)
{
    // Set ASK modulation type
    switch (mod_type)
    {
    case 0:
        viPrintf(instrument, "SOURce1:ASKey:STATe OFF\n");
        break;
    case 1:
        viPrintf(instrument, "SOURce1:ASKey:STATe ON\n");
        break;
    default:
        printf("Invalid modulation type\n");
        break;
    }
}
void Set_ASK_amplitude(double amplitude)
{
    // Set ASK amplitude (Vpp)
    viPrintf(instrument, "SOURce1:ASKey:AMPLitude %f\n", amplitude);
}
void Set_ASK_frequency(int rate_Hz)
{
    // Set ASK frequency
    // Note: The rate is the frequency of the ASK signal, not the rate of change of the frequency.
    viPrintf(instrument, "SOURce1:ASKey:INTernal:RATE %d\n", rate_Hz);
}