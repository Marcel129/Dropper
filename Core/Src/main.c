/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "box.h"

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM3){
		_dropper_StepIRQ();
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin == SEED_SENSOR_CHANNEL_1_PIN	 ||
			GPIO_Pin == SEED_SENSOR_CHANNEL_2_PIN ||
			GPIO_Pin == SEED_SENSOR_CHANNEL_3_PIN){
		_dropper_SeedSensorIRQ();
	}
	else if(GPIO_Pin == DROPPER_HOMING_SENSOR_PIN){
		_dropper_HomingSensorIRQ();
	}
}


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

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
	MX_TIM3_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	_dropper_Init();
	HAL_Delay(2000);

	GPIO_PinState s5 = HAL_GPIO_ReadPin(SENSOR_5_GPIO_Port, SENSOR_5_Pin);
	GPIO_PinState s6 = HAL_GPIO_ReadPin(SENSOR_6_GPIO_Port, SENSOR_6_Pin);
	GPIO_PinState s7 = HAL_GPIO_ReadPin(SENSOR_7_GPIO_Port, SENSOR_7_Pin);
	GPIO_PinState s8 = HAL_GPIO_ReadPin(SENSOR_8_GPIO_Port, SENSOR_8_Pin);
	GPIO_PinState s9 = HAL_GPIO_ReadPin(SENSOR_9_GPIO_Port, SENSOR_9_Pin);
	GPIO_PinState s10 = HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port, SENSOR_10_Pin);
	GPIO_PinState s11 = HAL_GPIO_ReadPin(SENSOR_11_GPIO_Port, SENSOR_11_Pin);
	GPIO_PinState s12 = HAL_GPIO_ReadPin(SENSOR_12_GPIO_Port, SENSOR_12_Pin);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		if(box_main_UART.msgReadyToRead) _dropper_execCmd();

		if(s5 != HAL_GPIO_ReadPin(SENSOR_5_GPIO_Port, SENSOR_5_Pin)){
			Communication_SendMsg("S5 zmienil stan\r\n");
			HAL_Delay(500);
		}
		if(s6 != HAL_GPIO_ReadPin(SENSOR_6_GPIO_Port, SENSOR_6_Pin)){
			Communication_SendMsg("S6 zmienil stan\r\n");
			HAL_Delay(500);
		}
		if(s7 != HAL_GPIO_ReadPin(SENSOR_7_GPIO_Port, SENSOR_7_Pin)){
			Communication_SendMsg("S7 zmienil stan\r\n");
			HAL_Delay(500);
			//dolny max
		}
		if(s8 != HAL_GPIO_ReadPin(SENSOR_8_GPIO_Port, SENSOR_8_Pin)){
			Communication_SendMsg("S8 zmienil stan\r\n");
			HAL_Delay(500);
			//dolny min
		}
		if(s9 != HAL_GPIO_ReadPin(SENSOR_9_GPIO_Port, SENSOR_9_Pin)){
			Communication_SendMsg("S9 zmienil stan\r\n");
			HAL_Delay(500);
		}
		if(s10 != HAL_GPIO_ReadPin(SENSOR_10_GPIO_Port, SENSOR_10_Pin)){
			Communication_SendMsg("S10 zmienil stan\r\n");
			HAL_Delay(500);
		}
		if(s11 != HAL_GPIO_ReadPin(SENSOR_11_GPIO_Port, SENSOR_11_Pin)){
			Communication_SendMsg("S11 zmienil stan\r\n");
			HAL_Delay(500);
		}
		if(s12 != HAL_GPIO_ReadPin(SENSOR_12_GPIO_Port, SENSOR_12_Pin)){
			Communication_SendMsg("S12 zmienil stan\r\n");
			HAL_Delay(500);
		}

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

	/** Configure the main internal regulator output voltage
	 */
	HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
	RCC_OscInitStruct.PLL.PLLN = 85;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
	RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
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
