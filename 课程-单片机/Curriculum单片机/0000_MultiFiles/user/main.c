#include "public.h"

void main(){
	test();
	light_the_x_th_led(1);
	lcd1602_init();//LCD1602初始化
	lcd1602_show_string(0,0,"DATE:24-05-21 #23");//第一行显示
	lcd1602_show_string(0,1,"TIME:19:03:12");//第二行显示
	while(1){
		
	}
}