/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "AnalysisCmd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern DAC_HandleTypeDef hdac;
extern UART_HandleTypeDef huart1;
uint8_t Buffer[1];
uint8_t UART_Buffer[2];
uint8_t UART_sta=0;
uint8_t UART_index = 0;
uint16_t freq=0;
uint16_t ADC_Value[100]={0};  
uint32_t Value=0;   //?????
float V=0;

// Buffer for Osc display
uint16_t Curve40_12bit_Buffer[2][80] = // 有40个采样点，每个点数据为12位深度，Curve40_12bit_Buffer[0]存储的是X坐标，Curve40_12bit_Buffer[1]存储的是Y坐标
{
  {
    100, 200, 300, 400, 500, 600, 700, 800, 900, 1000,
    1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000,
    2100, 2200, 2300, 2400, 2500, 2600, 2700, 2800, 2900, 3000,
    3100, 3200, 3300, 3400, 3500, 3600, 3700, 3800, 3900, 4000,

    4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000,
    0,0,0,0,0,0,0,0,0,0,
  },
  {
    10, 22, 40, 60, 78, 94, 110, 125, 144, 161,
    390, 1000, 2200, 1000, 750, 630, 590, 612, 800, 757,
    800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700,
    1800, 1900, 2000, 2100, 2200, 2300, 2400, 2500, 2600, 2700,

    0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0

  }
};

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

/**
 * @brief ?????c????getchar,scanf??USARTx
 * @retval None
 */
int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}

uint32_t getADC_bit(){
		// PA1
		int i;
		// average 
		for(i=0;i<10;i++)
			Value+=ADC_Value[i];
		Value/=10;
		HAL_Delay(10);
		return Value;
}

float getADC(){
		// PA1
		int i;
		// average 
		for(i=0;i<100;i++)
			Value+=ADC_Value[i];
		Value/=100;  
		V=Value*3300/4096;  //ADC????4096,??3300mV
		HAL_Delay(10);
		return V;
}

void update_curve_buffer(uint16_t frequency)
{
	uint32_t amp = 0;
	for(int i=0;i<100;i++)
			amp+=ADC_Value[i];
	amp/=100;
	// printf("ave_bit=%d\n", amp);
	// printf("curve update @ f=%d\n to %d",frequency, amp); // TEST
	if (frequency <= 40)
	{
		Curve40_12bit_Buffer[1][frequency-1] = amp;
    if (frequency == 1)
    {
      Curve40_12bit_Buffer[1][59] = amp;
      Curve40_12bit_Buffer[1][58] = amp;
      Curve40_12bit_Buffer[1][57] = amp;
      Curve40_12bit_Buffer[1][56] = amp;
      Curve40_12bit_Buffer[1][55] = amp;
    }
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
//	printf("HAL_UART_RxCpltCallback\n"); // TEST
  if (huart->Instance == USART1)
  {
//    HAL_UART_Transmit(&huart1, (uint8_t *)Buffer, 1, 0xffff);
//		printf("buf[0]=%d\nstatus=%d\n", Buffer[0], UART_sta);
		if(Buffer[0]==0xfe && UART_sta == 1) {
			UART_sta=0;
			UART_index=0;
			freq = UART_Buffer[0] | UART_Buffer[1] << 8;
			// Update curve buffer
      // printf("f=%d\n", freq); // TEST
      update_curve_buffer(freq);
		}
		else if(UART_sta==1)UART_Buffer[UART_index++]=Buffer[0];
    else if (Buffer[0]==0x05) UART_sta=1;
    HAL_UART_Receive_IT(&huart1, (uint8_t *)Buffer, 1);
  }
	
}

void SendCoordData(uint16_t* arrayX, uint16_t* arrayY, uint8_t length) {
	// example cmd (CMD_Crood << 8) | CMD_HEADER, (CMD_HEADER << 8) | CMD_Freq 
	// CMD_Crood fellow with a arry that [x1,y1,x2,y2,...]
		const uint8_t* array1 = (uint8_t*)arrayX;
		const uint8_t* array2 = (uint8_t*)arrayY;
		const uint16_t cmd_header = CMD_HEADER;
		const uint16_t cmd_coord = CMD_Crood;
		HAL_UART_Transmit(&huart1, (uint8_t*)&cmd_header, 1, 0xFFFF);  
    HAL_UART_Transmit(&huart1, (uint8_t*)&cmd_coord, 1, 0xFFFF);
    for(uint8_t i = 0; i < 40; i++) {
			
			// Send Xi
        HAL_UART_Transmit(&huart1, array1+2*i, 1, 0xFFFF);	// Send low byte first
        HAL_UART_Transmit(&huart1, array1+2*i+1, 1, 0xFFFF);     // Send high byte
			// Send Yi
        HAL_UART_Transmit(&huart1, array2+2*i, 1, 0xFFFF);	// Send low byte first
        HAL_UART_Transmit(&huart1, array2+2*i+1, 1, 0xFFFF);     // Send high byte
    }
    
    // uint8_t mid = 0xee;
		// HAL_UART_Transmit(&huart1, &mid, 1, 0xFFFF);	// Send End
		// HAL_UART_Transmit(&huart1, &mid, 1, 0xFFFF);	// Send End
		// HAL_UART_Transmit(&huart1, &mid, 1, 0xFFFF);	// Send End
		// HAL_UART_Transmit(&huart1, &mid, 1, 0xFFFF);	// Send End

		uint8_t end1 = END_1;
		uint8_t end2 = END_2;
		HAL_UART_Transmit(&huart1, &end1, 1, 0xFFFF);	// Send End
		HAL_UART_Transmit(&huart1, &end2, 1, 0xFFFF);	// Send End
}


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// PA4 DAC1, PA5 DAC2
// Sine Wave Data, 12 bit Deepth  @Test
// 1M Sampling Rate , 10k Freq
// 100 Point one cycle
const uint16_t Sine12bit[100]={	0x0800,0x0881,0x0901,0x0980,0x09FD,0x0A79,0x0AF2,0x0B68,0x0BDA,0x0C49,
0x0CB3,0x0D19,0x0D79,0x0DD4,0x0E29,0x0E78,0x0EC0,0x0F02,0x0F3C,0x0F6F,	0x0F9B,0x0FBF,0x0FDB,0x0FEF,0x0FFB,0x0FFF,0x0FFB,0x0FEF,0x0FDB,0x0FBF,
0x0F9B,0x0F6F,0x0F3C,0x0F02,0x0EC0,0x0E78,0x0E29,0x0DD4,0x0D79,0x0D19,
0x0CB3,0x0C49,0x0BDA,0x0B68,0x0AF2,0x0A79,0x09FD,0x0980,0x0901,0x0881,
0x0800,0x077F,0x06FF,0x0680,0x0603,0x0587,0x050E,0x0498,0x0426,0x03B7,	0x034D,0x02E7,0x0287,0x022C,0x01D7,0x0188,0x0140,0x00FE,0x00C4,0x0091,
0x0065,0x0041,0x0025,0x0011,0x0005,0x0001,0x0005,0x0011,0x0025,0x0041,
0x0065,0x0091,0x00C4,0x00FE,0x0140,0x0188,0x01D7,0x022C,0x0287,0x02E7,
0x034D,0x03B7,0x0426,0x0498,0x050E,0x0587,0x0603,0x0680,0x06FF,0x077F,
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DAC_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start(&htim2);
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t*)Curve40_12bit_Buffer[0],60,DAC_ALIGN_12B_R);// 100 is the DataSize, here transimit half word(16bit) once 
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_2,(uint32_t*)Curve40_12bit_Buffer[1],60,DAC_ALIGN_12B_R);
	
  HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Value,100);
	
  HAL_UART_Receive_IT(&huart1, (uint8_t *)Buffer, 1);
	
	//printf("start\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    /* USER CODE END WHILE */
//    Curve40_12bit_Buffer[1][4] = 4000;
//    HAL_Delay(1000);
//    Curve40_12bit_Buffer[1][4] = 0;
//    HAL_Delay(1000);
    SendCoordData(Curve40_12bit_Buffer[0], Curve40_12bit_Buffer[1], 40); // Send the data to the PC
		HAL_Delay(500);
    // printf("TEST\n");
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
