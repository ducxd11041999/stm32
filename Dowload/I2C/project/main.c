#include "stm32f10x.h"
#include "i2c_lcd.h" 

uint32_t Time_ST=0;							// bien delay bang system tick timer	

GPIO_InitTypeDef 					GPIO_InitStructure;
I2C_InitTypeDef						I2C_InitStructure;       // khai bao bien de su dung thu vien chuan I2C cua ST.

void GPIO_Configuration(void);
void Delay_ms(uint16_t time);
void Delay_msST(uint16_t nTime);              // ham delay tuyet doi bang system tick timer
void I2C_LCD_Configuration(void);              // chuong trinh con cau hinh I2C

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	GPIO_Configuration();
	I2C_LCD_Configuration();
	lcd_init ();                                 // ham khoi dong LCD16x2
	lcd_send_string ("GIAO TIEP I2C");
  while (1)
  {
		GPIO_WriteBit(GPIOB,GPIO_Pin_9,(BitAction)(1^GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)));
		Delay_ms(100);
  }
}

void GPIO_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void Delay_ms(uint16_t time)
{
uint32_t time_n=time*12000;
	while(time_n!=0){time_n--;}

}
void Delay_msST(uint16_t nTime)																			// ham delay tuyet doi
{
		Time_ST = nTime;
	while(Time_ST !=0)
			{
			}
}
void I2C_LCD_Configuration(void)
{
    // cap clock cho ngoai vi va I2C
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);							// su dung kenh I2C2 cua STM32
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    // cau hinh chan SDA va SCL
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;						//PB10 - SCL, PB11 - SDA
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    // cau hinh I2C
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = 0; // 
    I2C_InitStructure.I2C_Ack = I2C_Ack_Disable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;       
    I2C_InitStructure.I2C_ClockSpeed = 100000;										
    I2C_Init(I2C2, &I2C_InitStructure);
    // cho phep bo I2C hoat dong
    I2C_Cmd(I2C2, ENABLE);

}
