
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"

/* USER CODE BEGIN Includes */
#include "test.h"
#include "lis3dh.h"
#include "lis3dhDebug.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_I2C1_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
	/* USER CODE BEGIN 1 */
	status_t lis3dhretCode;
	int8_t temperature;
	uint8_t lis3dhStatus;
	//	uint8_t valueL,valueH;
	//	int16_t lis3dhAccX=-1, lis3dhAccY=-1,lis3dhAccZ=-1;
	AxesRaw_t lis3dhAxes;
	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

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
	MX_USART1_UART_Init();
	MX_I2C1_Init();
	/* USER CODE BEGIN 2 */
	printf("Rak811 LIS3DH accelerometer demo program\r\n");

	if (LIS3DH_Init())
		printf("main: lis3dh accelerometer successfully initialized\r\n");

	//  lis3dhPrintAllRegs();
	if (LIS3DH_SetODR((LIS3DH_ODR_t) LIS3DH_ODR_1Hz) != MEMS_SUCCESS)
		printf("main: Could not set sampling rate to 1 Hz\r\n");
	else
		printf("main: Sampling rate successfully set to 1 Hz\r\n");

	/*
  if (LIS3DH_SetFullScale(LIS3DH_FULLSCALE_8) != MEMS_SUCCESS)
	  printf("main: Could not set full scale to 8\r\n");
  else
	  printf("main: Full scale successfully set to 8\r\n");
	 */
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		if ((lis3dhretCode = LIS3DH_GetStatusReg(&lis3dhStatus)) != MEMS_SUCCESS)
			printf("main: Error when reading the status register\r\n");
		else {
			lis3dhretCode = MEMS_SUCCESS;
			printf("main: Status Reg before acceleration readout: 0x%02x\r\n",lis3dhStatus);
			/*
	      if (lis3dhStatus & LIS3DH_ZYXDA) {
	      lis3dhretCode &= LIS3DH_ReadReg(LIS3DH_OUT_X_L, &valueL);
	      lis3dhretCode &= LIS3DH_ReadReg(LIS3DH_OUT_X_H, &valueH);
	      lis3dhAccX = (valueH << 8) | valueL;

	      lis3dhretCode &= LIS3DH_ReadReg(LIS3DH_OUT_Y_L, &valueL);
	      lis3dhretCode &= LIS3DH_ReadReg(LIS3DH_OUT_Y_H, &valueH);
	      lis3dhAccY = (valueH << 8) | valueL;

	      lis3dhretCode &= LIS3DH_ReadReg(LIS3DH_OUT_Z_L, &valueL);
	      lis3dhretCode &= LIS3DH_ReadReg(LIS3DH_OUT_Z_H, &valueH);
	      lis3dhAccZ = (valueH << 8) | valueL;
	      }
	      if (lis3dhretCode) {
	      lis3dhAccX = lis3dhAccX >> 6;
	      lis3dhAccY = lis3dhAccY >> 6;
	      lis3dhAccZ = lis3dhAccZ >> 6;
	      printf("AccX : %d, AccY: %d, AccY: %d\r\n",lis3dhAccX,lis3dhAccY,lis3dhAccZ);
	      if (LIS3DH_GetStatusReg(&lis3dhStatus) == MEMS_SUCCESS)
	      printf("main: Status Reg after acceleration readout: 0x%02x\r\n",lis3dhStatus);
	      }
	      else
	      printf("main: Error when reading acceleration values\r\n");
	      }
			 */
			if (lis3dhStatus & LIS3DH_ZYXDA) {
				if (LIS3DH_GetAccAxes(&lis3dhAxes) != MEMS_SUCCESS)
					printf("main: Error when reading acceleration values\r\n");
				else
					printf("main: AccX : %d, AccY: %d, AccZ: %d\r\n",lis3dhAxes.AXIS_X,lis3dhAxes.AXIS_Y,lis3dhAxes.AXIS_Z);
			}

			/* check status bits for temperature acquisition */
			if ((lis3dhretCode = LIS3DH_ReadReg(LIS3DH_CTRL_REG4, &lis3dhStatus)) != MEMS_SUCCESS)
				printf("main: Error when reading control register 4\r\n");
			else {
				printf("main: register 4 content: 0x%02x\r\n",lis3dhStatus);
				if (lis3dhStatus & (MEMS_SET << LIS3DH_BDU))
					printf("main: BDU bit correctly set in control register 4\r\n");
				else
					printf("main: BDU bit is NOT set in control register 4\r\n");
			}
			/* check ADC_EN bit in temp cfg register */
			if ((lis3dhretCode = LIS3DH_ReadReg(LIS3DH_TEMP_CFG_REG, &lis3dhStatus)) != MEMS_SUCCESS)
				printf("main: Error when reading control register 4\r\n");
			else {
				printf("main: temp cfg register content: 0x%02x\r\n",lis3dhStatus);

				if (lis3dhStatus & (MEMS_SET << LIS3DH_ADC_EN) )
					printf("main: ADC enable bit correctly set in temp cfg register\r\n");
				else
					printf("main: ADC enable bit is NOT set in temp cfg register\r\n");

				if (lis3dhStatus & (MEMS_SET << LIS3DH_TEMP_EN) )
					printf("main: temperature enable bit correctly set in temp cfg register\r\n");
				else
					printf("main: temperature enable bit is NOT set in temp cfg register\r\n");
			}

			if ((lis3dhretCode = LIS3DH_GetTempRaw(&temperature)) != MEMS_SUCCESS)
				printf("main: Error when reading raw temperature\r\n");
			else {
				printf("main: temperature: %02d degrees C\r\n",(uint8_t)temperature);

			}

			HAL_Delay(10000);
			/* USER CODE END WHILE */

			/* USER CODE BEGIN 3 */

		}
		/* USER CODE END 3 */

	}
}

  /**
   * @brief System Clock Configuration
   * @retval None
   */
  void SystemClock_Config(void)
  {

	  RCC_OscInitTypeDef RCC_OscInitStruct;
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;

	  /**Configure the main internal regulator output voltage
	   */
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	  /**Initializes the CPU, AHB and APB busses clocks
	   */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LIS3DH_INT1_Pin LIS3DH_INT2_Pin */
  GPIO_InitStruct.Pin = LIS3DH_INT1_Pin|LIS3DH_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
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
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
