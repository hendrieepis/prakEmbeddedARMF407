/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#define BTN1_Pin GPIO_PIN_0
#define BTN1_GPIO_Port GPIOA
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
//static uint8_t temp_rxBuffer;
uint8_t inBuffer[] = "m";
uint8_t outBuffer[] = "M";

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef UartHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART_INIT(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
	HAL_Init();
	SystemClock_Config();
	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_SPI1_Init();
    MX_USART_INIT();
	HAL_UART_Transmit(&UartHandle, (uint8_t *)&"\n\r",2, 10);
	HAL_UART_Transmit(&UartHandle, (uint8_t *)&"Master SPI V1 \n\r",20, 1000);
	HAL_UART_Transmit(&UartHandle, (uint8_t *)&"Press button user to start.. \n\r",28, 10);
	while (HAL_GPIO_ReadPin(BTN1_GPIO_Port, BTN1_Pin) == GPIO_PIN_RESET)
	{
		HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_12);
		HAL_Delay(40);
	}
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);

	HAL_UART_Transmit(&UartHandle, (uint8_t *)&"Start Communication \n\r",21, 10);
	while (1)
	{
		switch(HAL_SPI_TransmitReceive(&hspi1, outBuffer, inBuffer, 1, 10000))
		{
		case HAL_OK:
			/* Communication is completed ____________________________________________*/
			HAL_UART_Transmit(&UartHandle, (uint8_t *)inBuffer,1, 10);
			break;

		case HAL_TIMEOUT:
			/* A Timeout occurred_____________________________________________________*/
			HAL_UART_Transmit(&UartHandle, (uint8_t *)"Err: HAL_TIMEOUT \n\r",20, 10);
			break;

			/* An Error occurred______________________________________________________*/
		case HAL_ERROR:
			HAL_UART_Transmit(&UartHandle, (uint8_t *)"Err: HAL_ERROR \n\r",20, 10);
			break;

		default:
			break;
		}
		HAL_Delay(300);
	}
}

/** System Clock Configuration
 */
void SystemClock_Config(void)
{

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	__HAL_RCC_PWR_CLK_ENABLE();

	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 4;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* SPI1 init function */
void MX_SPI1_Init(void)
{

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	hspi1.Init.Direction         = SPI_DIRECTION_2LINES;
	hspi1.Init.CLKPhase          = SPI_PHASE_1EDGE;
	hspi1.Init.CLKPolarity       = SPI_POLARITY_HIGH;
	hspi1.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial     = 7;
	hspi1.Init.DataSize          = SPI_DATASIZE_8BIT;
	hspi1.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	hspi1.Init.NSS               = SPI_NSS_SOFT;
	hspi1.Init.TIMode            = SPI_TIMODE_DISABLE;
	HAL_SPI_Init(&hspi1);

}

/** Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 */
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin : BTN1_Pin */
	GPIO_InitStruct.Pin = BTN1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BTN1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : userLED */
	__GPIOD_CLK_ENABLE();
	GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin=GPIO_PIN_12;
	GPIO_InitStruct.Pull=GPIO_NOPULL;
	GPIO_InitStruct.Speed=GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOD,&GPIO_InitStruct);

}

void MX_USART_INIT(void){
	__GPIOA_CLK_ENABLE();
	__USART2_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	//	GPIO_InitStruct.Pull = GPIO_NOPULL;  //uncomment if error
	//	GPIO_InitStruct.Speed = GPIO_SPEED_FAST; //uncomment if error
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	UartHandle.Instance = USART2;
	UartHandle.Init.BaudRate = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits = UART_STOPBITS_1;
	UartHandle.Init.Parity = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode = UART_MODE_TX_RX;
	HAL_UART_Init(&UartHandle);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */

}

#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
