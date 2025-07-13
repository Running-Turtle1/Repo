//所有公共的资源
#ifndef __PUBLIC_H__
#define __PUBLIC_H__

//声明类型重定义,一般在包含其他文件前，
typedef unsigned char 	u8;
typedef unsigned int 	u16;

//包含头文件
#include <reg52.h>
#include "led.h"
#include "key.h"
#include "smg.h"
#include "step_motor.h"
#include "iic.h"
#include "24c02.h"
#include "lcd1602.h"

#include "timer.h"
/********************（模块：LED应用）********************/
//LED:D1~D7:端口
#define LEDS_PORT 	P2
//LED:D1~D7
sbit LED_D1=P2^0;
sbit LED_D2=P2^1;
sbit LED_D3=P2^2;
sbit LED_D4=P2^3;
sbit LED_D5=P2^4;
sbit LED_D6=P2^5;
sbit LED_D7=P2^6;
sbit LED_D8=P2^7;
/********************（模块：KEY应用）********************/
//定义独立按键的位，同时也是外部输入中断INT0
sbit INT0_KEY_K3=P3^2;
sbit INT1_KEY_K4=P3^3;
//独立的KEY
sbit KEY_K1=P3^1;
sbit KEY_K2=P3^0;
sbit KEY_K3=P3^2;
sbit KEY_K4=P3^3;
/********************（模块：SMG应用）********************/
//使用宏定义数码管"段选"码端口
#define SMG_A_2_DP_PORT	P0	
//静态数码管“位选”码端口
sbit SMG_1_2_LS_A=P2^2;
sbit SMG_1_2_LS_B=P2^3;
sbit SMG_1_2_LS_C=P2^4;

extern u8 code g_smg_duan_code[];
/********************（STEP_MOTOR应用）********************/
//定义ULN2003控制步进电机管脚
//VCC——红色
//D——橙色
sbit STEP_MOTOR_IN_D=P1^0;
//C——黄色
sbit STEP_MOTOR_IN_C=P1^1;
//B——粉色
sbit STEP_MOTOR_IN_B=P1^2;
//A——蓝色
sbit STEP_MOTOR_IN_A=P1^3;
/********************（模块：IIC应用）********************/
//定义EEPROM控制脚
//SCL时钟线
sbit IIC_SCL=P2^1;
//SDA数据线
sbit IIC_SDA=P2^0;
/********************（模块：EEPROM应用）********************/

//定义数据存入EEPROM的起始地址
#define EEPROM_ADDRESS	0
/********************（模块：LCD1602应用）********************/
sbit LCD1602_RS=P2^6;
sbit LCD1602_RW=P2^5;
sbit LCD1602_E=P2^7;

#define LCD1602_DATA_PORT P0

extern u8 code lcd1602_table[];
	
/******************************
函数声明
******************************/
void delay_10us(u16 ten_us);
#endif