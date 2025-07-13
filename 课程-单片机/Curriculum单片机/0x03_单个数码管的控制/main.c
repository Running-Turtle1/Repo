/*
1.  一个数码管 8 段，每一段都是一个 LED
2. 数码管是共阴 : 置 1 亮
*/
#include "reg52.h"

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
void delay(u16 x){
	while(x --);
}

void main(){
	while(1){
		u16 i = 0;
		for(i = 0; i < 16; i ++){
			P0 = Array[i];
			delay();
		}
	}

}