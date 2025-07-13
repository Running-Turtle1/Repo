#include "public.h"

// 点亮单片机的第 x 个灯
void light_the_x_th_led(u16 x){
	P2 = 0xff; // 全部熄灭
	P2 &= ~(1 << x); // 将第 x 位置为 0
}

void waterfall_light(){
	u16 i, t;
	for(i = 0; i < 8; i ++){
		light_the_x_th_led(i); 
		delay_10us(500 * 100); // 延时 500 ms
	}
}