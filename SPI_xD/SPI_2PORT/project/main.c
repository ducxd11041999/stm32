#include "stm32f10x.h"

#define BufferSize 32


GPIO_InitTypeDef 					GPIO_InitStructure;
SPI_InitTypeDef   				SPI_InitStructure;
NVIC_InitTypeDef 					NVIC_InitStructure;

																						

void Delay_ms(uint16_t time);
void Delay_ns(uint16_t time);
void SPI1_Master_Con(void);


																						
int main(void)
{
//	SysTick_Config(SystemCoreClock/1000);
	SPI1_Master_Con();
	Delay_ms(10);
  while (1)
  {
		
		SPI_I2S_SendData(SPI1, 0x00);
		Delay_ms(1000);
  }
}

void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
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
		//SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;					
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;	
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;		
		SPI_InitStructure.SPI_CRCPolynomial = 7;
		SPI_Init(SPI1, &SPI_InitStructure);		
		
		SPI_Cmd(SPI1, ENABLE);	
	}



