#ifndef _GPIO_Config_H_
#define _GPIO_Config_H_
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
void GPIO_Config(void);
void Delay_ms(uint16_t Time_Del);
void toggleLed(void);
void toggleLedLeft();
void toggleLedRight();
//void GPIO_Uart();
#endif 
