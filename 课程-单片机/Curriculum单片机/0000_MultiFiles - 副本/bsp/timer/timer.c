#include "public.h"

/* 初始化 T0 计时器，使得 1ms 中断一次 */
void T0_1ms_init(){
	/*
	设定T0定时器模式 
	M1 = 0, M0 = 1, 工作方式 1, 16 位定时器/计数器
	*/
	TMOD = 0x01;
	
	/*
		设定定时器初值, 使得 1ms 中断一次
		两个 8 位计数器到 2^16 = 65536 会溢出
		机器周期大约为 1us,
		初始值设定为 64536 = 0xFC18 就能 1ms 中断一次(不精确)
	*/
	TH0 = 0xFC;
	TL0 = 0x18;
	
	// 开启定时器0 中断
	ET0 = 1;
	
	// 开启总中断
	EA = 1;
	
	// 开启计时器开关 TR0 
	TR0 = 1;
}

void T0_isr() interrupt 1{
	// 中断发生总次数
	static unsigned int counter = 0;
	// 当前需要点亮小灯的编号
	static unsigned int ledNum = 0;
	counter ++;
	if(counter == 1000){ // 1000 * 1 = 1000 ms
		counter = 0; 
		light_the_x_th_led(ledNum);
		ledNum ++;
		if(ledNum == 8) ledNum = 0;
	}
	// 保证 1ms 的计时器中断周期
	TH0 = 0xFC;
	TL0 = 0x18;
}