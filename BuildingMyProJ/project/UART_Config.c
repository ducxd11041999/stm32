#include "UART_Config.h"
USART_InitTypeDef UART_InitStructure;
//NVIC_InitTypeDef NVIC_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure1;
void Init_UART (void)
	{
		
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure1);
		
			GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA, &GPIO_InitStructure1);	

			UART_InitStructure.USART_BaudRate = 9600;
			UART_InitStructure.USART_WordLength = USART_WordLength_8b;
			UART_InitStructure.USART_StopBits = USART_StopBits_1;
			UART_InitStructure.USART_Parity = USART_Parity_No;
			UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART2, &UART_InitStructure);
			
			USART_ClearFlag(USART2, USART_IT_RXNE);
			USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
			USART_Cmd(USART2, ENABLE);
	}
void USART_SendNumber(USART_TypeDef* USARTx, uint32_t x)
{
  char value[10]; //a temp array to hold results of conversion
  int i = 0; //loop index
  
  do
  {
    value[i++] = (char)(x % 10) + '0'; //convert integer to character
    x /= 10;
  } while(x);
  
  while(i) //send data
  {
    USART_SendChar(USARTx, value[--i]); 
  }
}
void USART_SendString(USART_TypeDef* USARTx, char * str)
{
  while(*str != 0)
  {
    USART_SendChar(USARTx, *str);
    str++;
  }
}	
void USART_SendChar(USART_TypeDef* USARTx, uint16_t ch)
{
  while(!(USARTx->SR & USART_SR_TXE));
  USARTx->DR = ch;  
}