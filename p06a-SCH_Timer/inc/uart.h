/*
 * uart.h
 *
 *  Created on: Apr 10, 2016
 *      Author: hendri
 */

#ifndef UART_H_
#define UART_H_
#include <stdint.h>
void MX_USART2_UART_Init(void);
void print_UART2(uint8_t string[], uint8_t length);


#endif /* UART_H_ */
