#include "stm32f10x.h"
GPIO_InitTypeDef GPIO_InitStructure;
uint32_t time_de_lay;
void Init_GPIO()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

void Init_SysTick() //khong dung ngat
{
		SysTick->CTRL = 0x05; /////101
		SysTick->VAL = 0;
		SysTick->LOAD = 72000-1;	
}
void Delay_systick_v0(uint16_t time)
{
		time_de_lay = time;
		while(time_de_lay!=0)
			{
				while((SysTick->CTRL&0x10000)==0x10000)
					{
						time_de_lay--;
					}
			}
}
void delay_systick_v2_handler(uint16_t time)
	{
		time_de_lay = time;
		while(time_de_lay != 0);
	}

int main(void)
{
	Init_GPIO();
	SysTick_Config(SystemCoreClock/1000);
	//Init_SysTick();
  while (1)
  {
		GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)1^GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13));
		Delay_systick_v0(1000);
		//delay_systick_v2_handler(100);
  }
}




