#include "HMC241.h"

// void HMC241_Init(void)
// {
//     GPIO_InitTypeDef GPIO_InitStructure;
//     RCC_APB2PeriphClockCmd(HMC241_RCC_APB2Periph, ENABLE); // Enable GPIOB clock

//     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2; // Initialize pins for CTRLA and CTRLB
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Set pins as push-pull output
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // Set speed to 50 MHz
//     GPIO_Init(HMC241_GPIO, &GPIO_InitStructure); // Initialize GPIOB with the specified configuration

//     // Set default channel to RF1
//     HMC241_CTRLA = 0; // Set CTRLA to low
//     HMC241_CTRLB = 0; // Set CTRLB to low
// }

void HMC241_Set_Channel(u8 channel)
{
    if (channel == 1)
    {
        HMC241_CTRLA_CLR;
        HMC241_CTRLB_CLR;
    }
    else if (channel == 2)
    {
        HMC241_CTRLA_SET;
        HMC241_CTRLB_CLR;
    }
    else if (channel == 3)
    {
        HMC241_CTRLA_CLR;
        HMC241_CTRLB_SET;
    }
    else if (channel == 4)
    {
        HMC241_CTRLA_SET;
        HMC241_CTRLB_SET;
    }
    else
    {
        HMC241_CTRLA_CLR;
        HMC241_CTRLB_CLR;
    }
}

// void HMC241_Set_Channel_B(u8 channel)
// {
//     if (channel == 1)
//     {
//         HMC241_CTRLA_CLR;
//         HMC241_CTRLB_CLR;
//     }
//     else if (channel == 2)
//     {
//         HMC241_CTRLA_SET;
//         HMC241_CTRLB_CLR;
//     }
//     else if (channel == 3)
//     {
//         HMC241_CTRLA_CLR;
//         HMC241_CTRLB_SET;
//     }
//     else if (channel == 4)
//     {
//         HMC241_CTRLA_SET;
//         HMC241_CTRLB_SET;
//     }
//     else
//     {
//         HMC241_CTRLA_CLR;
//         HMC241_CTRLB_CLR;
//     }
// }