
#include "stm32f10x.h"
GPIO_InitTypeDef 			GPIO_InitStructure;
EXTI_InitTypeDef      EXTI_InitStructure;
NVIC_InitTypeDef      NVIC_InitStructure;
uint32_t Timingdelay;

void  Init_GPIO()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	}
void Init_Exti()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource14);
	
		EXTI_ClearITPendingBit(EXTI_Line14);
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Line = EXTI_Line14;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
	
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}
void delay_ms_sys_(uint16_t time)
	{
		Timingdelay = time;
		while(Timingdelay!=0)
			{
				while( (SysTick->CTRL&0x10000)==0x10000)
					{
						Timingdelay--;
					}
			}
	}
void de_lay_sysTick(uint16_t time_delay_)
	{
		Timingdelay = time_delay_;
		while(Timingdelay!=0);
	}
void SysTick_Init(void)
{
	SysTick->CTRL = 0x00000005;
	SysTick->VAL =0;
	SysTick->LOAD = 72000-1;
}
	
void EXTI15_10_IRQHandler(void)
{
		EXTI_ClearITPendingBit(EXTI_Line14);
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)));
		

}
int main(void)
{
	SysTick_Init();
	Init_GPIO();
  Init_Exti();
  while (1)
  {
	}
}


