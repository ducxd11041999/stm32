#include "GPIO_Config.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

GPIO_InitTypeDef GPIO_InitStructure;

void GPIO_Config(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_12;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	}
	
void Delay_ms(uint16_t Time_Del)
	{
		uint32_t Time = Time_Del * 12000;
		while(Time!=0)
			{
				Time--;
			}
	}
void toggleLed(void)
	{
		
	}
void toggleLedLeft()
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_8,0);
		GPIO_WriteBit(GPIOB,GPIO_Pin_13,1);
		Delay_ms(100);
	}
void toggleLedRight()
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_8,0);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,1);
		Delay_ms(100);
	}