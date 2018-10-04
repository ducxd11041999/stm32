#include "stm32f10x.h"

#define BufferSize 32


GPIO_InitTypeDef 					GPIO_InitStructure;
SPI_InitTypeDef   				SPI_InitStructure;
NVIC_InitTypeDef 					NVIC_InitStructure;
USART_InitTypeDef         UART_InitStructure;

																						
void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void Delay_ns(uint16_t time);
void SPI1_Master_Con(void);
void SPI2_Slave_Con(void);
void UART_Configuration (void);
																						
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	GPIO_Configuration();
	SPI1_Master_Con();
	SPI2_Slave_Con();
	Delay_ms(10);
	UART_Configuration();
  while (1)
  {
		
		  
		
  }
}
void UART_Configuration (void)
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

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction) (0));
}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}
void Delay_ns(uint16_t time)
{
uint32_t time_n=time*12;
	while(time_n!=0){time_n--;}

}
void SPI1_Master_Con(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1|RCC_APB2Periph_GPIOA, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5| GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;					
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;	
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;		
		//SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI1, &SPI_InitStructure);		
		
		SPI_Cmd(SPI1, ENABLE);	
	}
void SPI2_Slave_Con(void)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;					
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;	
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;		
		SPI_Init(SPI2, &SPI_InitStructure);			
		
		SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, DISABLE);
		SPI_Cmd(SPI2, ENABLE);	
		
		/* Configure and enable SPI_SLAVE interrupt --------------------------------*/
				NVIC_InitStructure.NVIC_IRQChannel = SPI2_IRQn;
				NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
				NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
				NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
				NVIC_Init(&NVIC_InitStructure);
	}



