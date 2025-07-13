#include "reg52.h"

/******** 原理博客 : https://blog.csdn.net/m0_50562428/article/details/130895466 ********/

typedef unsigned char u8;
typedef unsigned int u16;

// 数码管段选代码
u8 code Array[] = { 
    // 0 - f
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

/*
	矩阵键盘 P1 输入
	<行 : P17 - P14>
	<列 : P13 - P10>
	1 行 -> P17		1 列 -> P13
	2 行 -> P16		2 列 -> P12
	3 行 -> P15		3 列 -> P11
	4 行 -> P14		4 列 -> P10
*/

void delay_10us(u16 x){
	while(x --);
}


void main(){
	while(1){
		// 0xf7 : 1111 0111, 第一列接通低电平
		P1 = 0xf7;
		if(P1 != 0xf7){ // 检测按键是否按下
			delay_10us(1000); // 延时消抖
			while(P1 == 0x77){ // 检测按键 1 : 0111 0111  
                // 显示 LED 数字 1
                P0 = Array[0];
            }
            while(P1 == 0xb7){ // 检测按键 2 : 1011 0111
                // 显示 LED 数字 2
                P0 = Array[1];
            }
            while(P1 == 0xd7){ // 检测按键 3 : 1101 0111
                // 显示 LED 数字 3
                P0 = Array[2];
            }
            while(P1 == 0xe7){ // 检测按键 4 : 1110 0111
                // 显示 LED 数字 4
                P0 = Array[3];
            }
		}
		
		/*********** 按照检测第一列的方式控制剩余列 ************/
		
		// 0xfb : 1111 1011, 第二列接通低电平
		P1 = 0xfb;
		if(P1 != 0xfb){  
			delay_10us(1000); 
			while(P1 == 0x7b){  
                P0 = Array[4];
            }
            while(P1 == 0xbb){  
                P0 = Array[5];
            }
            while(P1 == 0xdb){  
                P0 = Array[6];
            }
            while(P1 == 0xeb){  
                P0 = Array[7];
            }
		}
		
		// 0xfd : 1111 1101, 第三列接通低电平
		P1 = 0xfd;
		if(P1 != 0xfd){  
			delay_10us(1000);  
			while(P1 == 0x7d){   
                P0 = Array[8];
            }
            while(P1 == 0xbd){  
                P0 = Array[9];
            }
            while(P1 == 0xdd){  
                P0 = Array[10];
            }
            while(P1 == 0xed){  
                P0 = Array[11];
            }
		}
		
		// 0xfd : 1111 1110, 第四列接通低电平
		P1 = 0xfe;
		if(P1 != 0xfe){  
			delay_10us(1000);  
			while(P1 == 0x7e){   
                P0 = Array[12];
            }
            while(P1 == 0xbe){  
                P0 = Array[13];
            }
            while(P1 == 0xde){  
                P0 = Array[14];
            }
            while(P1 == 0xee){  
                P0 = Array[15];
            }
		}
	}
    
}