#ifndef _public_H
#define _public_H

#include "reg52.h"

typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;


void delay_10us(u16 ten_us);
void delay_ms(u16 ms);

#endif


/*
// ds1302_write_byte(0x80,0X50); wjf
	// 秒寄存器addr=0x80, dat=0x50
	// 8421BCD码?
								 秒     分    时   日    月    星期   年
extern u8 g_WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C};

24 年, 星期一, 5月20日,16时41分50秒
extern u8 g_SET_RTC_TIME[7] = {0x50, 0x41, 0x16, 0x20, 0x05, 0x01, 0x24};

void ds1302_init(void){
	// DS1302 设置时间为 16时41分50秒
	
	// 寄存地址是 0x8E, 
	ds1302_write_byte(0x8E, 0x00); // 关闭写保护寄存器,写保护位, 关闭之后 MCU 才可以写入 RTC
	u8 i = 0;
	for(i = 0 ; i < 7; i ++){
		ds1302_write_byte(g_WRITE_RTC_ADDR[i], g_SET_RTC_TIME[i]);
	}
}
*/
