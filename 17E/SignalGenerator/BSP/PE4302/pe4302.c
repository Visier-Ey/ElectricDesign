#include "pe4302.h"

void PE4302_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // Enable GPIOB clock

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12; // Initialize pins for LE, CLK, and DATA
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Set pins as push-pull output
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Set speed to 50 MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure); // Initialize GPIOB with the specified configuration

    SERIAL_LE = 1; // Set LE high
    SERIAL_CLK = 0; // Set CLK low
    SERIAL_DATA = 0; // Set DATA low
}

void PE4302_Set_Attenuation(u8 attenuation) // Low 6 bits available
{
    u8 i;
    attenuation = attenuation << 2; // Shift left to align with PE4302's data format
    SERIAL_LE = 0; // Set LE low to start data transfer
    delay_us(1); // Small delay for stability
    for (i = 0; i < 6; i++)
    {
        SERIAL_CLK = 0; // Set CLK low
        delay_us(1); // Small delay for stability
        SERIAL_DATA = (attenuation & 0x80) ? 1 : 0; // Set DATA according to the current bit
        attenuation <<= 1; // Shift left to prepare for the next bit
        delay_us(1); // Small delay for stability
        SERIAL_CLK = 1; // Set CLK high to latch the data bit
        delay_us(1); // Small delay for stability
    }
    SERIAL_CLK = 0; // Set CLK low
    delay_us(1); // Small delay for stability
    SERIAL_DATA = 0; // Set DATA low for the last bit
    delay_us(1); // Small delay for stability
    SERIAL_LE = 1; // Set LE high to latch the data
}