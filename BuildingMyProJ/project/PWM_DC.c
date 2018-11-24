#include "PWM_DC.h"

GPIO_InitTypeDef GPIO_InitStructure2;
TIM_TimeBaseInitTypeDef		TIM_TimeBaseStructure;
TIM_OCInitTypeDef					TIM_OCInitStructure; 

void DIR_IO_init()
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_7;
		GPIO_Init(GPIOA, &GPIO_InitStructure2);
	}
void Init_PWM(void)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); ///cap xung clockc cho GPIO( yeu cau dung chan voi channel)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// cap xung cho timer 3
	

		GPIO_InitStructure2.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_0;
		GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure2);
	
	
  TIM_TimeBaseStructure.TIM_Prescaler = 0;    /// he so chia 7200 => F = 10kHz
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /// mode dem len
  TIM_TimeBaseStructure.TIM_Period = 999; ///// den tu 0-9999
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); ////cau hinh tim4 trong struct da thiet lap o tren

	///Dong co phai
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //mode OC 1-set 2-clear so sanh voi gia tri pulse 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; ////bat 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);


	////Dong co trai
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //mode OC 1-set 2-clear so sanh voi gia tri pulse 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; ////bat 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);
  TIM_Cmd(TIM3, ENABLE);
	}
	
void DC_CtrlSpeed(int left , int right)
	{
		DIR_IO_init();
		int PWM_L = left * 10;
		int PWM_R = right * 10;
		if(left >= 0)
			{
				GPIO_WriteBit(GPIOA, GPIO_Pin_4 , 0);
				GPIO_WriteBit(GPIOA, GPIO_Pin_5 , 1);
				TIM_SetCompare3(TIM3 , PWM_L);
			}
		else
			{
				TIM_SetCompare3(TIM3 , -PWM_L);
				GPIO_WriteBit(GPIOA, GPIO_Pin_4 , 1);
				GPIO_WriteBit(GPIOA, GPIO_Pin_5 , 0);
			
			}
		if(right >=0)
			{
				GPIO_WriteBit(GPIOA, GPIO_Pin_6 , 1);
				GPIO_WriteBit(GPIOA, GPIO_Pin_7 , 0);
				TIM_SetCompare4(TIM3 , PWM_R);
			}
		else
			{
				TIM_SetCompare4(TIM3 , -PWM_R);
				GPIO_WriteBit(GPIOA, GPIO_Pin_6 , 0);
				GPIO_WriteBit(GPIOA, GPIO_Pin_7 , 1);
				
			}
		
	}
void Init_Servo()
	{
		////pwm 2 channel 4
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); ///cap xung clockc cho GPIO( yeu cau dung chan voi channel)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);// cap xung cho timer 2
	

		GPIO_InitStructure2.GPIO_Pin  = GPIO_Pin_1;
		GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure2);

	
  TIM_TimeBaseStructure.TIM_Prescaler = 1439;    /// he so chia 7200 => F = 10kHz
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /// mode dem len
  TIM_TimeBaseStructure.TIM_Period = 999; ///// den tu 0-9999
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); ////cau hinh tim4 trong struct da thiet lap o tren

	///SERVO
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //mode OC 1-set 2-clear so sanh voi gia tri pulse 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; ////bat 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);

	}
void DC_CtrlAngle(int Angle)
	{
		float Goc;
		if(Angle < -90)
			Angle = -90;
		if(Angle > 90)
			Angle = 90;
		if(Angle <= 0)
			{
				Goc = (float)(65 + 0.45* Angle); 
				TIM_SetCompare2(TIM2,	Goc );		
			}
		else
			{
				Goc = (float)(65 + 0.5* Angle); 
				TIM_SetCompare2(TIM2, Goc );		
			}
	}