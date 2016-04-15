

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ֱ����� ��������	   
//wlx
//��������:2016/1/16
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) wlx 2016-2026
//All rights reserved
//********************************************************************************
//˵��
//V1.0 20160116
//��������ֱ�����ǰ����ת
////////////////////////////////////////////////////////////////////////////////// 	 

#define MOTOR_LEFT_L 0  
#define MOTOR_LEFT_H 1   

#define MOTOR_RIGHT_L 2  
#define MOTOR_RIGHT_H 3  

#include "sys.h"
#include "timer.h"
#include "motor.h"

u32 g_timer_arr = 500-1;   //�趨�������Զ���װֵ 
u32 gao =10;
u32 di =130;

TIM_TypeDef * PWM_BASE[4] = {	TIM10, TIM11, TIM13, TIM14};

void pwm_start(u32 pwm)
{
	PWM_BASE[pwm]->CCR1 = gao;
}

void pwm_slow(u32 pwm)
{
	PWM_BASE[pwm]->CCR1 = di+gao;
}


void pwm_stop(u32 pwm)
{
	PWM_BASE[pwm]->CCR1 = g_timer_arr;
}

void l_motor_forward()
{
	pwm_start(MOTOR_LEFT_H);
	pwm_stop(MOTOR_LEFT_L);
}

void l_motor_backward()
{
	pwm_start(MOTOR_LEFT_L);
	pwm_stop(MOTOR_LEFT_H);
}

void l_motor_stop()
{
	pwm_stop(MOTOR_LEFT_H);
	pwm_stop(MOTOR_LEFT_L);
}
void l_motor_slow()
{
	pwm_start(MOTOR_LEFT_H);
	pwm_slow(MOTOR_LEFT_L);
}
void r_motor_forward()
{
	pwm_start(MOTOR_RIGHT_H);
	pwm_stop(MOTOR_RIGHT_L);
}

void r_motor_backward()
{
	pwm_start(MOTOR_RIGHT_L);
	pwm_stop(MOTOR_RIGHT_H);
}

void r_motor_stop()
{
	pwm_stop(MOTOR_RIGHT_H);
	pwm_stop(MOTOR_RIGHT_L);
}

void r_motor_slow()
{
	pwm_start(MOTOR_RIGHT_H);
	pwm_slow(MOTOR_RIGHT_L);
}

void car_forward()
{
	l_motor_forward();
	r_motor_forward();
}

void car_backward()
{
	l_motor_backward();
	r_motor_backward();
}

void car_left()
{
	l_motor_stop();
	r_motor_forward();
}
void car_left_slow()
{
	l_motor_slow();
	r_motor_forward();
}
void car_left_back()
{
	l_motor_backward();
	r_motor_forward();
}
void car_right()
{
	l_motor_forward();
	r_motor_stop();
}
void car_right_slow()
{
	r_motor_stop();
	r_motor_slow();
}
void car_right_back()
{
	r_motor_backward();
	l_motor_forward();
}
void car_stop()
{
	l_motor_stop();
	r_motor_stop();
}

void pwm_init()
{
	TIM10_PWM_Init(g_timer_arr,84-1);	//1Mhz�ļ���Ƶ��,2Khz��PWM.     
	TIM11_PWM_Init(g_timer_arr,84-1);	//1Mhz�ļ���Ƶ��,2Khz��PWM.     
	TIM13_PWM_Init(g_timer_arr,84-1);	//1Mhz�ļ���Ƶ��,2Khz��PWM.     
	TIM14_PWM_Init(g_timer_arr,84-1);	//1Mhz�ļ���Ƶ��,2Khz��PWM.     
}
