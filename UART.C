
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
void SystemClock_Config(void);


int main(void)
{


  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  int counter = 0;
  int adcValue = 0;
  char msg_00[50];
  while (1){
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  adcValue = HAL_ADC_GetValue(&hadc1);
    counter++;
	  if(counter == 50){counter = 0;}
	  	  	  sprintf(msg_00,"Hex => 0x%X Decimal => %d ADC => %d\r\n",counter,counter,adcValue);
	  		  HAL_UART_Transmit(&huart2, (uint8_t *) msg_00, strlen(msg_00), HAL_MAX_DELAY);
	  		  HAL_Delay(100);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                           