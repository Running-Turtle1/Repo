#include "reg52.h"
sbit k1 = P3 ^ 1;
sbit k2 = P3 ^ 0;
sbit k3 = P3 ^ 2;
sbit k4 = P3 ^ 3;

typedef unsigned char u8;
typedef unsigned int u16;

u8 code Array[] = {
    // 0 ~ f
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71  // F
};

void delay(u16 x) {
	while(x --);
}

void main() {
	while(1) {
		if(!k1 || !k2 || !k3 || !k4) {
			if(k1 == 0) {
				delay(1000);
				while(!k1);
				P0 = Array[1];
				delay(500 * 100);
			} else if(k2 == 0) {
				delay(1000);
				while(!k2);
				P0 = Array[4];
				delay(500 * 100);
			} else if(k3 == 0) {
				delay(1000);
				while(!k3);
				P0 = Array[7];
				delay(500 * 100);
			} else {
				delay(1000);
				while(!k4);
				P0 = Array[9];
				delay(500 * 100);
			}
		}
		else{
			P0 = 0x00;
		}
	}
}

 