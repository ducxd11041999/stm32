
#include "stm32f10x.h"
GPIO_InitTypeDef  GPIO_InitStructure;
EXTI_InitTypeDef  EXTI_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;

void Init_GPIO()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}



void Init_Exti()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	
	EXTI_ClearITPendingBit(EXTI_Line5);
	EXTI_InitStructure.EXTI_Line= EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
int main(void)
{
  Init_Exti();
	Init_GPIO();
	 GPIO_WriteBit(GPIOC,GPIO_Pin_13,1);
  while (1)
  {
		 
  }
}
void EXTI9_5_IRQHandler()
{
	EXTI_ClearITPendingBit(EXTI_Line5);
  GPIO_WriteBit(GPIOC,GPIO_Pin_13,1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13));
}
