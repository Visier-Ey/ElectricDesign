/**
 ******************************************************************************
 * @file    DG4202.h
 * @author  Isaac Huang
 * @brief   This file contains the common defines and functions prototypes for the
 *          RIGOL DG4202 function generator. Based on the VISA library, SCPI commands
 *          are used to control the instrument.
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DG4202_H__
#define __DG4202_H__

/* Includes ------------------------------------------------------------------*/
#include <visa.h>

// DG4202 Instrument Resource Name
#define DG4202_NAME "USB0::0x1AB1::0x0641::DG4E264101726::INSTR"

enum Waveform
{
    SINE,
    SQUARE,
    TRIANGLE,
    PULSE
};

// DG4202 Instrument Basic Functions
int DG4202_Init();       // Connect to the instrument
char *DG4202_ReadID();   // Read the instrument ID
int DG4202_Disconnect(); // Disconnect from the instrument
void Channel1_ON();    // Enable Channel 1

// DG4202 Instrument Set Functions
void Set_frequency(int frequency);    // Set Wave Frequency
void Set_amplitude(double amplitude); // Set Wave Amplitude
void Set_waveform(int waveform);      // Set Waveform Type (Sine, Square, Triangle, Pulse)
// Set FM Modulation
void Set_FM(int mod_type);            // Set FM Modulation Type (0: Off, 1: On)
void Set_FM_frequency(int frequency); // Set FM Modulation Frequency
void Set_FM_deviation(int deviation); // Set FM Deviation
// Set AM Modulation
void Set_AM(int mod_type);            // Set AM Modulation Type (0: Off, 1: On)
void Set_AM_frequency(int frequency); // Set AM Modulation Frequency(Hz)
void Set_AM_depth(int depth_percent); // Set AM Modulation Depth (%)
// Set FSK Modulation
void Set_FSK(int mod_type);            // Set FSK Modulation Type (0: Off, 1: On)
void Set_FSK_frequency(int frequency); // Set FSK Frequency (Hz)
void Set_FSK_Rate(int rate);           // Set FSK Rate (Hz)
void Set_FSK_Polarity(int positive); // Set FSK Polarity (0: Negative, 1: Positive)
// Set ASK Modulation
void Set_ASK(int mod_type);            // Set ASK Modulation Type (0: Off, 1: On)
void Set_ASK_amplitude(double amplitude); // Set ASK Amplitude (Vpp)
void Set_ASK_frequency(int frequency); // Set ASK Frequency (Hz)

#endif // __DG4202_H__