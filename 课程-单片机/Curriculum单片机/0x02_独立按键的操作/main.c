#include "reg52.h"

void delay(unsigned int count) {
    while(count --);
}

// 定义按键和LED连接的引脚, 其中独立按键对应的引脚分别是 1 0 2 3
sbit key1 = P3^1;
sbit key2 = P3^0;
sbit key3 = P3^2;
sbit key4 = P3^3;

sbit led1 = P2^0;
sbit led2 = P2^1;
sbit led3 = P2^2;
sbit led4 = P2^3;

void main(){
	key1 = 1; // 设置为输入模式
	key2 = 1;
	key3 = 1;
	key4 = 1;
	led1 = 0; // 设置为输出模式
	led2 = 0;
	led3 = 0;
	led4 = 0;
	while(1) {
		// 读取按键状态，按键按下时为0，否则为 1
		if(!key1){
			delay(1000); // 延时消除按键抖动
			while(!key1); // 等待按键释放
			led1 = !led1; // 取反，实现LED的亮灭切换
		}
		
		if(!key2){
			delay(1000); // 延时消除按键抖动
			while(!key2); // 等待按键释放
			led2 = !led2; // 取反，实现LED的亮灭切换
		}
		
		if(!key3){
			delay(1000); // 延时消除按键抖动
			while(!key3); // 等待按键释放
			led3 = !led3; // 取反，实现LED的亮灭切换
		}
		
		if(!key4){
			delay(1000); // 延时消除按键抖动
			while(!key4); // 等待按键释放
			led4 = !led4; // 取反，实现LED的亮灭切换
		}
	}
}

