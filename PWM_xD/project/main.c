#include "stm32f10x.h"

GPIO_InitTypeDef					GPIO_InitStructure;
TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
TIM_OCInitTypeDef					TIM_OCInitStructure; 

void Delay_ms(uint16_t time);
void TIM4_Configuraion(void);
void init_gpio()
	{
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOC,&GPIO_InitStructure);		

	}
void delay(uint16_t time)
	{
		uint16_t time_delay= time *12000;
		while(time_delay!= 0)
		{
			time_delay--;
		}
		
	}
int main(void)
{
	
	TIM4_Configuraion();
   
  while (1)
  {
//		for(int i=0;i<=10000;i+=5)
//		{
//     
//			delay(10);
//		}
	}
}

void TIM4_Configuraion(void)
{

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); ///cap xung clockc cho GPIO( yeu cau dung chan voi channel)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);// cap xung cho timer 4
	

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
  TIM_TimeBaseStructure.TIM_Prescaler = 7199;    /// he so chia 7200 => F = 10kHz
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /// mode dem len
  TIM_TimeBaseStructure.TIM_Period = 9999; ///// den tu 0-9999
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); ////cau hinh tim4 trong struct da thiet lap o tren


  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //mode OC 1-set 2-clear so sanh voi gia tri pulse 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; ////bat 
 TIM_OCInitStructure.TIM_Pulse = 10000; ////gia tri pulse so sanh => do rong xung can thiet lap(co the thay the bang ham setcompare)
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; 
  TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM4, ENABLE);
  TIM_Cmd(TIM4, ENABLE);
}
