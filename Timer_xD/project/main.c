#include "stm32f10x.h"

GPIO_InitTypeDef 					GPIO_InitStructure;
TIM_TimeBaseInitTypeDef		TIM_TimeBaseInitStructure;
NVIC_InitTypeDef					NVIC_InitStructure;
void Init_GPIO(void);
void Init_Timer_4(void);
int main(void)
{
	Init_GPIO();
	Init_Timer_4();
	
  while (1)
  {
		
		
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

void Init_Timer_4(void)
{	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
		TIM_TimeBaseInitStructure.TIM_Prescaler = 7199;
		TIM_TimeBaseInitStructure.TIM_Period = 9999;
		TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);  
		TIM_ITConfig( TIM4, TIM_IT_Update, ENABLE); 
		TIM_Cmd(TIM4, ENABLE); 
		
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);	
}


