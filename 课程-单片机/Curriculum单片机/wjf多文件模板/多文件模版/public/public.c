#include "public.h"
/***************************
函数名称：void delay_10us(u16 ten_us)
函数功能：定义延时函数10us
输入	: u16 ten_us(最长延时65536*10us)
输出	：void
***************************/
void delay_10us(u16 ten_us)
{
 	while(ten_us--);
}