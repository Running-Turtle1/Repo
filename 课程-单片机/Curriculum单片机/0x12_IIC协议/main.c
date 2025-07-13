#include "reg52.h"

/*
	IIC 协议, 用在 
*/

// https://blog.csdn.net/as480133937/article/details/105366932

// 定义I2C总线的相关引脚和控制寄存器
sbit SCL = P1^0; // 串行时钟线 : Serial Clock Line
sbit SDA = P1^1; // 串行数据线 : Serial Data Line
 
void delay_10us(unsigned int x){
	while(x --);
}	

void i2c_start() {
	/**** 空闲状态 / 初始状态  ***/
	/*
		因为IIC的 SCL 和SDA 都需要接上拉电阻，保证空闲状态的稳定性
		所以IIC总线在空闲状态下SCL 和SDA都保持高电平
	*/
	SCL = 1;
    SDA = 1;
	delay_10us(1);
	
    // 发送起始信号 : SCL 不变, SDA 由高电平变为低电平
    SDA = 0;
	delay_10us(1);
	
    // SCL由高电平变为低电平，产生下降沿
	// 在I2C通信中，时钟线（SCL）的下降沿通常被用来触发数据的传输或接收。
	// 完成起始信号的形成 
    SCL = 0;
	delay_10us(1);
}

void i2c_stop() {
	// 初始状态
    SDA = 0;
    SCL = 1;
	delay_10us(1);
	
    // 发送停止信号 : SCL保持高电平, SDA由低电平变为高电平。
    SDA = 1;
	delay_10us(1);
}

/****  IIC发送一个字节数据  ****/
/*
	总结 : 
	1. 在 SCL 为高电平期间，发送数据，发送8次数据，
	   数据为 1 ,SDA被拉高 ; 数据为 0，SDA被拉低。  
	2. 传输期间保持传输稳定，所以数据线仅可以在时钟 SCL 为低电平时改变。
*/
void i2c_send_byte(unsigned char byte) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        // 发送每一位数据
        SDA = (byte & 0x80) ? 1 : 0; // 先发送高位
        byte <<= 1;
		delay_10us(1);
		
		// 保持 SDA 上的数据不变， 用于发送
        SCL = 1;
		delay_10us(1);
		
        // SCL由高电平变为低电平，产生下降沿
		// 可以开始进行下一次发送
        SCL = 0;
		delay_10us(1);
    }
}


// C51 单片机读取一个字节的数据 
/*
	总结 : 
	1. 在 SCL 为高电平期间，发送数据，发送8次数据，
	   数据为 1 ,SDA被拉高 ; 数据为 0，SDA被拉低。  
	2. 传输期间保持传输稳定，所以数据线仅可以在时钟 SCL 为低电平时改变。
*/
unsigned char i2c_read_byte() {
    unsigned char i, byte = 0;
    SDA = 1; // 允许从设备将数据拉低
    for (i = 0; i < 8; i++) {
        SCL = 1;
        byte = (byte << 1) | SDA; // 接收数据
        SCL = 0;
    }
    return byte;
}

//void i2c_init() {
//    // 初始化I2C总线
//    SDA = 1;
//    SCL = 1;
//}

void main() {
    unsigned char dat;
    i2c_init(); // 初始化I2C总线
    
    i2c_start(); // 发送起始信号
    i2c_send_byte(0xA0); // 发送设备地址（写模式）
    i2c_send_byte(0x00); // 发送数据地址
    i2c_send_byte(0x55); // 发送数据
    i2c_stop(); // 发送停止信号
    
    i2c_start(); // 发送起始信号
    i2c_send_byte(0xA0); // 发送设备地址（写模式）
    i2c_send_byte(0x00); // 发送数据地址
    i2c_start(); // 发送重复起始信号
    i2c_send_byte(0xA1); // 发送设备地址（读模式）
    dat = i2c_receive_byte(); // 接收数据
    i2c_stop(); // 发送停止信号
    
    while (1);
}
