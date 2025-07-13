#include "reg52.h"

// 参考博客 : https://blog.csdn.net/qq_65980796/article/details/131996779

sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;

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

/* 初始化 T1 计时器，使得 50ms 中断一次 */
void T1_50ms_init(){
	// 设定T1定时器模式 : 工作在方式1, 16位定时器 
	TMOD |= 0x10;
	
	// 50ms 中断一次 : 65536 - 50 * 1000 = 15536 = 0x3CB0
	TH1 = 0x3C;
	TL1 = 0xB0;
	
	// 开启定时器0 中断
	ET1 = 1;
	// 开启总中断
	EA = 1;
	
	// 开启计时器开关 TR0 
	TR1 = 1;
}

void main(){
	// 初始化定时器
	T0_1ms_init();
	T1_50ms_init();
	while(1){
		
	}
}

void T0_isr() interrupt 1{
	// 1s 使得小灯1 翻转一次
	static unsigned int counter = 0;
	counter ++;
	if(counter == 1000){ // 1000 * 1 = 1000 ms
		counter = 0; 
		LED0 = !LED0;
	}
	// 保证 1ms 的计时器中断周期
	TH0 = 0xFC;
	TL0 = 0x18;
}

void T1_isr() interrupt 3{
	// 1s 使得小灯2 翻转一次
	static unsigned int counter = 0;
	counter ++;
	if(counter == 20){ // 50 * 20 = 1000 ms
		counter = 0; 
		LED1 = !LED1;
	}
	// 保证 50ms 的计时器中断周期
	TH1 = 0x3C;
	TL1 = 0xB0;
}