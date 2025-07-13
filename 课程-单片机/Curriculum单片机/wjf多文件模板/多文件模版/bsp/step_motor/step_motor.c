#include "public.h"

/******************************************************
函数名称：void step_motor_4_beat_send_pulse(u8 dir,u8 step)
函数功能：步进电机-发送脉冲-控制程序
输入	: 	u8 dir
			dir=1:逆时针旋转
			dir=0:顺时针旋转
			u8 step
输出	：void
******************************************************/
void step_motor_4_beat_send_pulse(u8 dir,u8 step)
{
	u8 temp=step;
	
	if(dir==0)	//如果为逆时针旋转
		temp=3-step;//调换节拍信号
	switch(temp)//8个节拍控制：
	{
		//->D
		case 0: STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//->C
		case 1: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//B
		case 2: 
			   	STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=0;
				break;
		//CB
		case 3: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=1;
				break;
		 //停止相序
		default:
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;	
	}			
}
/******************************************************
函数名称：void step_motor_8_beat_send_pulse(u8 dir,u8 step)
函数功能：步进电机-发送脉冲-控制程序
输入	: 	u8 dir
			dir=1:逆时针旋转
			dir=0:顺时针旋转
			u8 step
输出	：void
******************************************************/
void step_motor_8_beat_send_pulse(u8 dir,u8 step)
{
	u8 step_temp=step;
	if(dir=0)
	{
	   step_temp=7-step;
	}
	switch(step_temp)
	{
		//->D
		case 0: STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//->DC
		case 1: 
				STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//C
		case 2: 
			   	STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;
		//CB
		case 3: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=1;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=0;
				break;
		//B
		case 4: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=0;
				break;
		//BA
		case 5: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=1;
				STEP_MOTOR_IN_A=1;
				break;
		//A
		case 6: 
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=1;
				break;
		//AD
		case 7: 
				STEP_MOTOR_IN_D=1;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=1;
				break;
		 //停止相序
		default:
				STEP_MOTOR_IN_D=0;
				STEP_MOTOR_IN_C=0;
				STEP_MOTOR_IN_B=0;
				STEP_MOTOR_IN_A=0;
				break;				
	}	
}
