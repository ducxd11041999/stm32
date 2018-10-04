#include "stm32f10x.h"

GPIO_InitTypeDef 					GPIO_InitStructure;	//GPIO struct
EXTI_InitTypeDef 					EXTI_InitStructure; // EXTI struct
NVIC_InitTypeDef 					NVIC_InitStructure; // NVIC struct

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void  EXTI_Configuration(void);
int main(void)
{
	GPIO_Configuration();
	EXTI_Configuration();
  while (1)
  {
	
  }
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void  EXTI_Configuration(void)
	{
		//cap clock cho ngat ngoai va ngoai vi
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOC, &GPIO_InitStructure);		
		/* mapping */
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource13);
		/* Clear the the EXTI line interrupt pending bit */
		EXTI_ClearITPendingBit(EXTI_Line13);
		/*EXTI line Configuration */
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStructure.EXTI_Line = EXTI_Line13;
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStructure);
		/*NVIC Configuration*/
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	void EXTI15_10_IRQHandler(void)
{
if(EXTI_GetITStatus(EXTI_Line14) != RESET)
	{	
		EXTI_ClearITPendingBit(EXTI_Line14);
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)));
		Delay_ms(100);
	
	}
}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}
