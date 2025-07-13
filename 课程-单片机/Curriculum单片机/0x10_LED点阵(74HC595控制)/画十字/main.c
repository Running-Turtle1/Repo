#include "reg52.h"

/* data, RCLK 是预定义变量*/

int i, j, k = 0;
sbit SER = P3^4; // 串行数据输入引脚
sbit SRCLK = P3^6; // 移位时钟输入引脚
sbit RCLK_ = P3^5; // 存储时钟输入引脚

void delay_ten_us(int x){
	while(x --);
}

// 上升沿时数据寄存器的数据移位。Q0->Q1->Q2-->Q3-->...-->Q7;下降沿移位寄存器数据不变。
void SRCLK_down(){
	SRCLK = 0;
	delay_ten_us(1);
	SRCLK = 1;
	delay_ten_us(1);
}

// 12 脚 : 上升沿时移位寄存器的数据进入数据存储寄存器，下降沿时存储寄存器数据不变。
void RCLK_down(){
	RCLK_ = 0;
	delay_ten_us(1);
	RCLK_ = 1;
	delay_ten_us(1);
}

// 写入数据
void hc595_write_data(int data_){
	int i;
	for(i = 7; i >= 0; i --){
		SER = data_ >> i & 1;
		SRCLK_down();
	}		
	RCLK_down();
}
/*
01111111
10111111
11011111
11101111
11110111
11111011
11111101
11111110
*/
unsigned char code col[8] = {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe};

// 画十字每行代码
unsigned char code led_matrix_row_codes[8] = {
	0x18,0x18,0x18,0xFF,0xFF,0x18,0x18,0x18
};
void main(){
	P0 = 0xff;
	hc595_write_data(0x00);
	while(1){
		for(i = 0; i < 8; i ++){
			hc595_write_data(led_matrix_row_codes[i]);
			P0 = col[i];
			delay_ten_us(100);
			P0 = 0xff;
		}
	}
	
}