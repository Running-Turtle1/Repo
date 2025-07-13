 // 外部中断 0 1 介绍 : https://blog.csdn.net/m0_56399733/article/details/133904885
#include "reg52.h"

typedef unsigned int u16;	 
typedef unsigned char u8;

// 统计 K3 按下的次数 , 即 INT0 发生中断的次数 
u16 press_button_k3_cnt = 0;

// 定义 LED1 和 LED2 管脚
sbit LED1=P2^0;
sbit LED2=P2^1;

// 定义独立按键 K3 和 K4 控制脚
// 独立按键K3连接的是外部中断0的引脚
sbit KEY3=P3^2;
sbit KEY4=P3^3;

void delay_10us(u16 ten_us) {
	while(ten_us--);	
}

// 外部中断 0 配置函数
void exit0_init() {
	IT0 = 1; // 跳变沿触发方式（下降沿）
	EX0 = 1; //打开INT0的中断允许
	EA = 1;  //打开总中断
}
// 外部中断 1 配置函数
void exit1_init() {
	IT1 = 1; //跳变沿触发方式（下降沿）
	EX1 = 1; //打开INT0的中断允许
	EA = 1;  //打开总中断
}

// 数码管段选代码
u8 code Array[] = { 
    // 0 - f
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71  // F
};

sbit pin0 = P2 ^ 2;
sbit pin1 = P2 ^ 3;
sbit pin2 = P2 ^ 4;

void main() {	
	exit0_init(); //外部中断0配置
	exit1_init(); //外部中断1配置
	pin0 = 1;
	pin1 = 1;
	pin2 = 1;
	while(1) {
		P0 = Array[press_button_k3_cnt]; // 第一个数码管显示按键次数
		delay_10us(100); //防止段码清零过快导致显示的数字亮度较低
		P0 = 0x00; //消影 段码清零
	}		 
}

void exit0() interrupt 0 //外部中断 0 中断函数
{
	delay_10us(1000); // 消抖
	if(KEY3 == 0){ // 再次判断K3键是否按下
		while(!KEY3); // 等待按键松开
		press_button_k3_cnt ++;
		if(press_button_k3_cnt == 10){
			press_button_k3_cnt = 0;	
		}
		LED1 =! LED1; //LED1状态翻转
	}			
}
void exit1() interrupt 2 //外部中断 1 中断函数
{
	delay_10us(1000); //消抖
	if(KEY4 == 0){ //再次判断 K4 键是否按下
		while(!KEY4);
		LED2 =! LED2; //LED2状态翻转
	}			
}