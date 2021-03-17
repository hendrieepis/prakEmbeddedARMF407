#include "uart.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

UART_HandleTypeDef huart2;
///*BEGIN printf ---------------------------------------------------------------*/
//#ifdef __GNUC__
//#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif /* __GNUC__ */
//
//PUTCHAR_PROTOTYPE
//{
////  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
//  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 10);
//  return ch;
//}
///* END printf ---------------------------------------------------------------- */

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 100);
//    __HAL_UART_FLUSH_DRREGISTER(&huart2);
//    fflush(stdout); // This will flush any pending printf output
	return ch;
}
/* USER CODE END PFP */

void MX_USART2_UART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_USART2_CLK_ENABLE();
	/**USART2 GPIO Configuration
	    PA2     ------> USART2_TX
	    PA3     ------> USART2_RX
	 */
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_8;
	HAL_UART_Init(&huart2);
}

void print_UART2(uint8_t string[], uint8_t length){
    HAL_UART_Transmit(&huart2, (uint8_t*)string, length, 5);
}
/*
 * //print out static text
sprintf(buffer,"Hello\r\n");
len=strlen(buffer);
HAL_UART_Transmit(&huart1, buffer, len, 1000);

//print out variable
sprintf(buffer,"This is i:%i\r\n",i);
len=strlen(buffer);
HAL_UART_Transmit(&huart1, buffer, len, 1000);
 */
