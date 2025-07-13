#include "public.h"

u8 time_buf[8]; // 用于 LCD 显示

char date_str[17]; // 日期字符串，长度为16字符+1个结束符
char time_str[17]; // 时间字符串，长度为16字符+1个结束符

u16 x;

void main(){
	lcd1602_init();//LCD1602初始化
	ds1302_init();//初始化DS1302
	
	while(1){
		ds1302_read_time(); // 读取 DS1302 的时间
		LcdDisplay(); // LCD1602 显示时间
	}
}