#include "reg52.h"

/*
编码原理   ： https://blog.csdn.net/m0_74068921/article/details/131619565
数码管消影 ： https://blog.csdn.net/weixin_66540418/article/details/132414077
*/

typedef unsigned char u8;
typedef unsigned int u16;

u8 code Array[16] = {
    // 0 ~ f
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

u16 code ctrl_74hc138[8][3] = {
	{0, 0, 0}, {1, 0, 0}, 
	{0, 1, 0}, {1, 1, 0},
	{0, 0, 1}, {1, 0, 1}, 
	{0, 1, 1}, {1, 1, 1}
};

void delay(u16 x){
	while(x --);
}

/* 
74hc138 译码器, 简称 38 译码器
下面是对应三个引脚的位 
*/
sbit pin0 = P2 ^ 2;
sbit pin1 = P2 ^ 3;
sbit pin2 = P2 ^ 4;

void main(){
	u16 i;
	while(1){
		// 位选 数码管 : 控制第 i 个数码管
		for(i = 0; i < 8; i ++){ 
			pin0 = ctrl_74hc138[i][0];
			pin1 = ctrl_74hc138[i][1];
			pin2 = ctrl_74hc138[i][2];
			P0 = Array[i];
			delay(100);
			P0 = 0x00; // 消除残影
		}
	}
}
