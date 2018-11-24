#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "GPIO_Config.h"
#include "UART_Config.h"
#include "PWM_DC.h"
int main()
	{
		uint16_t data;
		GPIO_Config();
		//GPIO_Uart();
		Init_UART();
		Init_PWM();
		DIR_IO_init();
		Init_Servo();
			while(1)
				{
				
				
				while(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
						{
							DC_CtrlAngle(0);
							DC_CtrlSpeed(0,0);
								data = USART_ReceiveData(USART2);	
							switch(data)
							{
								case 'L':
								{
												DC_CtrlAngle(-30);	
												toggleLedLeft();
												break;
												
								}
								case 'R':
								{
												DC_CtrlAngle(30);	
												toggleLedRight();
												break;
								}
								case 'F':
									{
										DC_CtrlSpeed(100,100);
										break;
									}
								case 'B':
									{
										DC_CtrlSpeed(-100,-100);
										break;
										
									}
								case 'G':
									{
										DC_CtrlSpeed(20,100);
										DC_CtrlAngle(-25);
										
										toggleLedLeft();
										break;
									}
								case 'I':
									{
										DC_CtrlAngle(20);
										DC_CtrlSpeed(100,20);
										toggleLedRight();
										break;
									}
								case 'H':
									{
										DC_CtrlSpeed(-25,-100);
										toggleLedLeft();
										DC_CtrlAngle(-20);
										break;
									}
									case 'J':
									{
										DC_CtrlSpeed(-100,-25);
										toggleLedRight();
										DC_CtrlAngle(20);
										break;
									}
								
								default :
									{
										DC_CtrlSpeed(0,0);
										DC_CtrlAngle(0);
										GPIO_WriteBit(GPIOB,GPIO_Pin_12,0);
										GPIO_WriteBit(GPIOB,GPIO_Pin_13,0);
										break;
									}
								}	
					}
			}
	}