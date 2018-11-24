#ifndef _PWM_DC_H_
#define _PWM_DC_H_
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
void Init_PWM(void);
void DC_CtrlSpeed(int left , int right);
void Init_Servo(void);
void DC_CtrlAngle(int Angle);
void DIR_IO_init();
#endif