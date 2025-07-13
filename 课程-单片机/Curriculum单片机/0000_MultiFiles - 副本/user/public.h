#ifndef __PUBLIC_H__
#define __PUBLIC_H__

typedef unsigned char u8;
typedef unsigned int u16;

// 包含系统头文件
#include "reg52.h"

// 包含自己写的头文件, 注意要添加头文件的目录
#include "Eight_Multiple_Eight_LED_Matrix.h"
#include "timer.h"
//#include "LCD1602.h"
//#include "DS1302.h"

sbit LCD1602_RS=P2^6;//数据命令选择
sbit LCD1602_RW=P2^5;//读写选择
sbit LCD1602_E=P2^7; //使能信号
#define LCD1602_DATAPORT P0	//宏定义LCD1602数据端口

// 函数声明
void delay_10us(u16 ten_us);

#endif