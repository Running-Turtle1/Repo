#include "reg52.h"

sbit LED0 = P2 ^ 0;
sbit LED1 = P2 ^ 1;

void T0_1ms_init(){
	// 设定T0定时器模式 : 工作在方式1, 16位定时器 
	TMOD = 0x01;
	
	/*
		设定定时器初值, 使得 1ms 中断一次
		两个 8 位计数器到 2^16 = 65536 会溢出
		机器周期为 1us,
		初始值设定为 64536 = 0xFC18 就能 1ms 中断一次
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

void T1_50ms_init(){
	// 设定T0定时器模式 : 工作在方式1, 16位定时器 
	TMOD |= 0x10;
	
	// 50ms 中断一次
	TH1 = 0x3C;
	TL1 = 0xB0;
	
	// 开启定时器0 中断
	ET1 = 1;
	// 开启总中断
	EA = 1;
	
	// 开启计时器开关 TR0 
	TR1 = 1;
}
/***********************************************************/
// 这节课的内容 : 
/*
	51 单片机不是驱动, 而是控制
	感性元件 : 
	ULN2003 最高不超过 50V
	in : 1, out : 0
	in : 0, out : ?
*/

sbit dc_motor_pin = P1 ^ 0; // 定义 dc2003 引脚
void delay_ten_us(int x){
	while(x --);
}
void DC_MOTOR_INIT(){
	// 关闭电机
	dc_motor_pin = 0;
}
void main(){
	DC_MOTOR_INIT();
	delay_ten_us(1000 * 100);
	delay_ten_us(1000 * 100);
	delay_ten_us(1000 * 100);
	T0_1ms_init();
	T1_50ms_init();
	while(1){
		
	}
}
/***********************************************************/
void T0_isr() interrupt 1{
	// 1s 使得小灯1 翻转一次
	// 1s 使得电机改变一次状态
	static unsigned int counter = 0;
	counter ++;
	if(counter == 1000){ // 1000 ms
		counter = 0; 
		LED0 = !LED0;
		dc_motor_pin = !dc_motor_pin;
	}
	// 保证 1ms 的计时器中断周期
	TH0 = 0xFC;
	TL0 = 0x18;
}

void T1_isr() interrupt 3{
	// 1s 使得小灯2 翻转一次
	static unsigned int counter = 0;
	counter ++;
	if(counter == 20){ // 1000 ms
		counter = 0; 
		LED1 = !LED1;
	}
	// 保证 50ms 的计时器中断周期
	TH1 = 0x3C;
	TL1 = 0xB0;
}