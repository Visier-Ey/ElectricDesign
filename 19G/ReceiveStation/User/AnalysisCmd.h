#ifndef ANALYSIS_CMD_H
#define ANALYSIS_CMD_H
#include "AD9854.h"
// ! PROTOCOL HEADER
// the first byte idenetify the command
// the second check the legitimacy

#define CMD_HEADER 0x05
#define CMD_DATA 0x02
#define ANALY_ERROR 0x01
#define ANALY_OK 0x00
#define ACK 0x06
#define NACK 0x15

// ! WORK MODE COMMANDS
#define FSK_CMD 0x11
#define BPSK_CMD 0x12 
#define OSK 0x13
#define AM 0x14
#define RFSK 0x15
#define CHIRP 0x16

// ! ACTION COMMANDS
#define INIT 0x21
#define SET_FSK 0x22
#define SET_BPSK 0x23
#define SET_OSK 0x24
#define SET_AM 0x25
#define SET_RFSK 0x26

// ! Define the Ack
#define TACK() printf("%c%c%c", 0x55, 0xAA,ACK)
#define TNACK() printf("%c%c%c", 0x55, 0xAA,NACK)


// ! Template

#define TEST 1
// ! Due to the LOWER BIT FIRST
uint8_t LowerToHigh(uint8_t *data, uint8_t len) {
    uint8_t temp, i;
#if TEST
    printf("Original Data: ");
    for (i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    printf("Data: %d\n", *(uint32_t*)data);
    printf("\n");
#endif
    for (i = 0; i < len / 2; i++) {
        temp = data[i];
        data[i] = data[len - i - 1];
        data[len - i - 1] = temp;
    }

#if TEST
    printf("Converted Data: ");
    for (i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
    printf("Data: %d\n", *(uint32_t*)data);
    printf("\n");
#endif
    return len;  
}

uint8_t AnalysisCmd(uint8_t *cmd, uint8_t len) {
    uint32_t var1, var2, var3, var4;
    uint16_t var5, var6;
    uint8_t var7;
    if (len < 2) return ANALY_ERROR;
    if (cmd[0] != CMD_HEADER)   return ANALY_ERROR;
    switch (cmd[1]) {
    case FSK_CMD:
        if (cmd[2]==INIT){ 
            AD9854_InitFSK();
        }
        else if(cmd[2]==SET_FSK) {
            if (len < 11) return ANALY_ERROR;
             var1 = *(uint32_t*)(cmd+7);
             var2 = *(uint32_t*)(cmd+3);
            AD9854_SetFSK(var1, var2);
        }else return ANALY_ERROR;
        break;
    case BPSK_CMD:
        if (cmd[2]==INIT) AD9854_InitBPSK();
        else if(cmd[2]==SET_BPSK) {
            if (len < 11) return ANALY_ERROR;
            var5 = *(uint16_t*)(cmd+3);
            var6 = *(uint16_t*)(cmd+7);
            AD9854_SetBPSK(var5, var6);
        }else return ANALY_ERROR;
        break;
    case OSK:
        if (cmd[2]==INIT) AD9854_InitOSK();
        else if(cmd[2]==SET_OSK) {
            if (len < 7) return ANALY_ERROR;
            var7 = cmd[3];
            AD9854_SetOSK(7);
        }else return ANALY_ERROR;
        break;
    case AM:
        if (cmd[2]==INIT) AD9854_InitAM();
        else if(cmd[2]==SET_AM) {
            if (len < 7) return ANALY_ERROR;
            var6 = *(uint16_t*)(cmd+3);
            AD9854_SetAM(var6);
        }else return ANALY_ERROR;
        break;
    case RFSK:
        if (cmd[2]==INIT) AD9854_InitRFSK();
        else if(cmd[2]==SET_RFSK) {
            if (len < 19) return ANALY_ERROR;
            var1 = *(uint32_t*)(cmd+3);
            var2 = *(uint32_t*)(cmd+7);
            var3 = *(uint32_t*)(cmd+11);
            var4 = *(uint32_t*)(cmd+15);
            AD9854_SetRFSK(var1, var2, var3, var4);
        }else return ANALY_ERROR;
        break;
    case CHIRP:
    // TODO: CHIRP
        break;
    default:
        return ANALY_ERROR;
    }
    return ANALY_OK;  
}

#endif
