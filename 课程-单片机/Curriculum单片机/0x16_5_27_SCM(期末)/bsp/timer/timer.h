#ifndef __TIMER_H__
#define __TIMER_H__


/*
	TMOD : 
	M0
	M1
	C/T_
	GATE
	M0
	M1
	C/T_
	GATE
*/

/* 初始化 T0 计时器，使得 1ms 中断一次 */
void T0_1ms_init();
void T0_50ms_init();
void T0_isr();
 
#endif