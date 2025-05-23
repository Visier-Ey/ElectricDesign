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
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "AD9854.h"
#include "HMC241.h"
#include "CD4051.h"
#include "math.h"
#include "FFT.h"
#include "CmdAnalysis.h"
// #include "CmdAnalysis.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PRODUCTION_MODE 1
#define DEVELOPMENT_MODE 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern UART_HandleTypeDef huart1;
uint8_t Buffer[1];
uint16_t adc_buff1[FFT_LENGTH];
uint16_t adc_buff3[FFT_LENGTH];

// ! AM,FM parmeter here
float amModu = 0.f;
float fmModu = 0.f;
uint16_t mainFreqAM = 1000;
uint16_t mainFreqFM = 1000;
uint16_t up=1000;
uint16_t down=1000;
uint16_t mode = 0;


uint8_t CarrierFreq = 20;
uint16_t AmpAMMax = 0;
uint16_t AmpFMMax = 0;
uint16_t AmpAMMin = 99999;
uint16_t AmpFMMin = 99999;
// uint32_t AmpAveAM = 0;
// uint32_t AmpAveFM = 0;

extern float thrid_output_F;

extern float thrid_output_A;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
// ! USART HERE
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xffff);
  return ch;
}

int fgetc(FILE *f)
{
  uint8_t ch = 0;
  HAL_UART_Receive(&huart1, &ch, 1, 0xffff);
  return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    CarrierFreq = Buffer[0];
    if (Buffer[0] == 'T') {
      printf("%f", amModu);
    }
    HAL_UART_Receive_IT(&huart1, (uint8_t *)Buffer, 1);
  }
}
// ! PROGRAM HERE


#define length 20
uint16_t last_length = 20;
uint16_t _last_AmpAMMax[length] = {0};
uint16_t _last_AmpAMMin[length] = {0};
uint16_t _last_AmpFMMax[length] = {0} ;
uint16_t _last_AmpFMMin[length] = {0} ;

void extract_both_amplitudes() {
  float _AmpAMMax = 0;
  float _AmpAMMin = 0xFFFF;
  float _AmpFMMax = 0;
  float _AmpFMMin = 0xFFFF;
  // 处理AM信号
  for (int i = 0; i < last_length-1; i++)
  {
    _last_AmpAMMax[i] = _last_AmpAMMax[i+1];
    _last_AmpAMMin[i] = _last_AmpAMMin[i+1];
    _last_AmpFMMax[i] = _last_AmpFMMax[i+1];
    _last_AmpFMMin[i] = _last_AmpFMMin[i+1];
  }
  
  _AmpAMMax = 0;
  _AmpAMMin = 0xFFFF;
  _AmpFMMax = 0;
  _AmpFMMin = 0xFFFF;
  
  for(int i = 0; i < FFT_LENGTH; i++) {
      // 处理AM信号
      if(adc_buff1[i] > _AmpAMMax) _AmpAMMax = adc_buff1[i];
      if(adc_buff1[i] < _AmpAMMin) _AmpAMMin = adc_buff1[i];
      
      // 处理FM信号
      if(adc_buff3[i] > _AmpFMMax) _AmpFMMax = adc_buff3[i];
      if(adc_buff3[i] < _AmpFMMin) _AmpFMMin = adc_buff3[i];
  }
  _last_AmpAMMax[last_length-1] = _AmpAMMax;
  _last_AmpAMMin[last_length-1] = _AmpAMMin;
  _last_AmpFMMax[last_length-1] = _AmpFMMax;
  _last_AmpFMMin[last_length-1] = _AmpFMMin;
  AmpAMMax = sum(_last_AmpAMMax, last_length) / last_length;
  AmpAMMin = sum(_last_AmpAMMin, last_length) / last_length;
  AmpFMMax = sum(_last_AmpFMMax, last_length) / last_length;
  AmpFMMin = sum(_last_AmpFMMin, last_length) / last_length;

  // 自动更新调制参数
  amModu = (float)(AmpAMMax - AmpAMMin) / (AmpAMMax + AmpAMMin);
  fmModu = (float)(AmpFMMax - AmpFMMin);
}


uint16_t calculateMaxFreqOffset(float modu)
{
  //! modu = max/mainfreq
  return modu * mainFreqFM;
}

uint8_t judgeCW(){
  if (AmpAMMax-AmpAMMin<200 && AmpFMMax-AmpFMMin<150) return 1;
  else return 0;
}



void judgeAMFMCW(float am, float fm)
{
  uint8_t _am = am > 0.08f ? 1 : 0;
  uint8_t _fm = fm > 0.06f ? 1 : 0;
  uint8_t _fsk = thrid_output_F > 0.04 ? 1 : 0;
  uint8_t _ask = thrid_output_A > 0.06 ? 1 : 0;
  if (mainFreqFM == 3000)
    _fsk = thrid_output_F > 0.017 ? 1 : 0;
  else if (mainFreqFM == 2000)
  {
    _fsk = thrid_output_F > 0.03 ? 1 : 0;
  }
  
  #if DEVELOPMENT_MODE
    printf("FSK:%.3f\t ASK:%.3f\n",thrid_output_F,thrid_output_A);
  #endif
  if(judgeCW() == 1) {
    #if DEVELOPMENT_MODE
      printType(JudgeType(CW_TYPE));
    #endif
    #if PRODUCTION_MODE
      CW();
      Modulation(0);
      ModFreq(0);
      OffsetFreq(0);
      Kf(0);
      Rc(0);
    #endif
  } else {
    // ! classified as No-CW
    if (AmpAMMax-AmpAMMin<200) {
      HMC241_Set_Channel(2);
      // ! classified as FM or FSK
      if (_fsk == 1 ) {
        #if DEVELOPMENT_MODE
          printType(JudgeType(FSK_TYPE));
        #endif
        CD_4051_SetChannel(4);
        #if PRODUCTION_MODE
          FSK();
          Modulation(0);
          ModFreq(mainFreqFM*10);  
          OffsetFreq(0);
          Kf((int)round(calculateFSKShift(fmModu,mainFreqFM))*100);
          Rc(20*mainFreqFM);
        #endif
      } else {
        #if DEVELOPMENT_MODE
          printType(JudgeType(FM_TYPE));
        #endif
        CD_4051_SetChannel(3);
        #if PRODUCTION_MODE
          FM();
          Modulation((int)round(calculateFMModulate(fmModu,mainFreqFM)*100));
          ModFreq(mainFreqFM*10);
          OffsetFreq((int)round(calculateMaxFreqOffset(calculateFMModulate(fmModu,mainFreqFM)))*10);
          Kf(0);
          Rc(0);
        #endif
      }
    } else {
      HMC241_Set_Channel(3);
      if (_ask == 1) {
        // ! classified as ASK
        #if DEVELOPMENT_MODE
          printType(JudgeType(ASK_TYPE));
        #endif
        CD_4051_SetChannel(2);
        #if PRODUCTION_MODE
          ASK();
          Modulation(0);
          ModFreq(mainFreqAM*10);
          OffsetFreq(0);
          Rc(20*mainFreqAM);
          Kf(0);
        #endif
      } else {
        // ! classified as AM
        #if DEVELOPMENT_MODE
          printType(JudgeType(AM_TYPE));
        #endif
        CD_4051_SetChannel(3);
        #if PRODUCTION_MODE
          AM();
          Modulation((int)round(calculateAMModulate(amModu,CarrierFreq)*100));
          ModFreq(mainFreqAM*10);
          OffsetFreq(0);
          Kf(0);
          Rc(0);
        #endif
      }
    }
  }
}

void loop()
{
  mainFreqAM = round(find_dominant_frequency(adc_buff1, 100000,2)/100)*100;
  mainFreqFM = round(find_dominant_frequency(adc_buff3,100000,1)/100)*100;
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buff1, FFT_LENGTH);
  HAL_ADC_Start_DMA(&hadc3, (uint32_t *)adc_buff3, FFT_LENGTH);
  extract_both_amplitudes();
  #if DEVELOPMENT_MODE
    printf("amModu:%.3f\r\n",calculateAMModulate(amModu,CarrierFreq));
  #endif

  judgeAMFMCW(calculateAMModulate(amModu,CarrierFreq), calculateFMModulate(fmModu,mainFreqFM));

  HAL_Delay(50);
}
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
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_USART1_UART_Init();
  MX_TIM8_Init();
  /* USER CODE BEGIN 2 */
  AD9854_Init();
  HAL_Delay(10);
  AD9854_SetSine(75000000, 2047);
  HAL_UART_Receive_IT(&huart1, (uint8_t *)Buffer, 1);

  HAL_TIM_Base_Start(&htim8);
  HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buff1, 1024);
  HAL_ADC_Start_DMA(&hadc3, (uint32_t *)adc_buff3, 1024);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  
  HMC241_Set_Channel(3);
  CD_4051_SetChannel(3);
  while (1)
  {
    loop();
    /* USER CODE END WHILE */

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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
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
