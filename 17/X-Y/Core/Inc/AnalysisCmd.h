#ifndef ANALYSIS_CMD_H
#define ANALYSIS_CMD_H
#include "main.h"
// ! PROTOCOL HEADER
// the first byte idenetify the command
// the second check the legitimacy

#define CMD_HEADER 0x05
#define CMD_Crood 0x02
#define CMD_Freq 0x02
#define ANALY_ERROR 0x01
#define ANALY_OK 0x00
#define END_1 0xfe
#define END_2 0xfe
#define ACK 0x06
#define NACK 0x15



#endif
