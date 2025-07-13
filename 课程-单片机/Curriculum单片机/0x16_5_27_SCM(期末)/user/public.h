#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef unsigned char u8;
typedef unsigned int u16;

// 包含系统头文件
#include "reg52.h"

// 包含自己写的头文件, 注意要添加头文件的目录
#include "LCD.h"
#include "DS.h"
#include "DS18.h"
#include "intrins.h" /////// _nop_();
#include "timer.h"

// LCD.h
sbit LCD1602_RS=P2^6;//数据命令选择
sbit LCD1602_RW=P2^5;//读写选择
sbit LCD1602_E=P2^7; //使能信号
#define LCD1602_DATAPORT P0	//宏定义LCD1602数据端口


// DS.h
//管脚定义
sbit DS1302_RST=P3^5;//复位管脚
sbit DS1302_CLK=P3^6;//时钟管脚
sbit DS1302_IO=P3^4;//数据管脚

//变量声明
extern u8 gDS1302_TIME[7];//存储时间

// DS18.h
//管脚定义
sbit DS18B20_PORT=P3^7;	//DS18B20数据口定义

// 函数声明
void delay_10us(u16 ten_us);

#endif