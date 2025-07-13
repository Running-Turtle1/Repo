#include "reg52.h"

void light_x_th_led(int x){
	P2 = 0xff;
	P2 &= ~(1 << x);
}

void waterfall_light(){
	int i, t;
	for(i = 0; i < 8; i ++){
		light_x_th_led(i);
		t = 500 * 100; // ÑÓÊ± 500 ms
		while(t --);
	}
}

void main(){
	while(1){
		waterfall_light();
	}
}