#ifndef _UART_Config_
#define _UART_Config_
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"

void Init_UART(void);
void USART_SendNumber(USART_TypeDef* USARTx, uint32_t x);
void USART_SendChar(USART_TypeDef* USARTx, uint16_t ch);
void USART_SendString(USART_TypeDef* USARTx, char * str);
#endif