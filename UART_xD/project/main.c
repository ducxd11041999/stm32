#include "stm32f10x.h"
#include <stdio.h>
/*Khoi tao bien cau hinh*/
GPIO_InitTypeDef			GPIO_InitStructure;
USART_InitTypeDef			UART_InitStructure;
NVIC_InitTypeDef			NVIC_InitStructure;



void Init_UART (void);
void USART_SendNumber(USART_TypeDef* USARTx, uint32_t x);
void USART_SendChar(USART_TypeDef* USARTx, uint16_t ch);
void Init_GPIO(void);
void USART_SendString(USART_TypeDef* USARTx, char * str);
int main(void)
{
	
	Init_GPIO();
	Init_UART();
  while (1)
  {
		//USART_SendString(USART3, "HuuDucXD\n");
	
//			USART_SendData(USART3,'1');
//		USART_SendNumber(USART3, 1+1);
//    	Delay_ms(200);
  }
}

void Init_GPIO(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}
void Init_UART (void)
	{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStructure);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
			UART_InitStructure.USART_BaudRate = 9600;
			UART_InitStructure.USART_WordLength = USART_WordLength_8b;
			UART_InitStructure.USART_StopBits = USART_StopBits_1;
			UART_InitStructure.USART_Parity = USART_Parity_No;
			UART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			UART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			USART_Init(USART3, &UART_InitStructure);
		
			NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
			
			
			USART_ClearFlag(USART3, USART_IT_RXNE);
			

			USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

			
			USART_Cmd(USART3, ENABLE);
	
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