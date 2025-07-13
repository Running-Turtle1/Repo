#include "reg52.h"
typedef unsigned char u8;
typedef unsigned int u16;

void delay_ten_us(int x){
	while(x --);
}

/*
	8 ÐÐ 5 ÁÐ
	32 * 8 * 5 = 1280dot
*/

#define LCD1602_DATA_PORT P0

sbit LED_RS = P2 ^ 6;
sbit LED_RW = P2 ^ 5; 
sbit LED_EN = P2 ^ 7; 

void main(){

}