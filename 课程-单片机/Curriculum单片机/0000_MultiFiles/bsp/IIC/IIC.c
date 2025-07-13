#include "public.h"

/*
	SDA, SCL 一定要有上拉电阻 (10K)
	IIC 总线空闲时, SDA = SCL = 1;
	当 SCL=1 时, SDA 上的数据不能改变
	当 SCL=0 时, SDA 上的数据可以改变
	
	AT24C02 256 个字节
	1 0 1 0 A2 A1 A0 R/W(读写标志位) --> 读是 1, 写是 0
	1 0 1 0 0  0  0  0
	
	通过 IIC 总线找到地址为 1010, 000 的 24C02 (EEPROM), 在地址为 0x01 的寄存器中写入数据 0x0F
	
	01 - 启动 IIC 总线, --> iic_start();
	02 - 写入 24C02 芯片地址 (1010,000) + W (写信号 0) --> iic_write_byte(0xA0);
	03 - 主机等待正确的 ASK 信号 --> iic_wait_ask();
	04 - 写入 24C02 地址 = 0x01 寄存器 -->  iic_write_byte(0x01);
	05 - 主机等待正确的 ASK 信号 --> iic_wait_ask();
	06 - 写入数据 0x0F -->  iic_write_byte(0x0F);
	07 - 主机等待正确的 ASK 信号 --> iic_wait_ask();
	08 - 停止 IIC 总线 --> iic_stop();
*/

/**********************************************
函数名称 : void iic_start()
函数功能 : IIC 总线开始信号 (启动IIC总线)
输入 : void
输出 : void
**********************************************/
void iic_start(){
	// 初始状态 = 空闲状态
	IIC_SCL = 1; // 时钟信号
	IIC_SDA = 1; // 数据信号
	delay_10us(1);
	
	// 起始信号 : SCL = 1, SDA 从 1 --> 0 (下降沿)
	IIC_SDA = 0;
	delay_10us(1);
	
	// 1- 代表
	// 2- 代表可以进行下一次的发送和接受
	IIC_SCL = 0;
	delay_10us(1);
}

/**********************************************
函数名称 : void iic_stop()
函数功能 :  
输入 : void
输出 : void
**********************************************/
void iic_stop(){
	// 初始状态
	IIC_SCL = 1;
	IIC_SDA = 0;
	delay_10us(1);
	
	// 终止信号， SCL = 1, SDA 从 0 --> 1 (上升沿)
	IIC_SDA = 1;
	delay_10us(1);
	
	// IIC 总线停止后, 进入空闲状态, SCL = 1, SDA = 1, 这里不用写
}

/**********************************************
函数名称 : iic_write_byte()
函数功能 :  
输入 : u8 dat
	   1 0 1 0 0 0 0
输出 : void
**********************************************/
void iic_write_byte(u8 dat){
	u8 i;
	// 发送第一位时, 为了要改变 SDA 上的数据 
	IIC_SCL = 0;
	delay_10us(1);
	
	for(i = 0; i < 8; i ++){
		if((dat & 0x80) > 0){
			IIC_SDA = 1;
		}
		else{
			IIC_SDA = 0;
		}
		dat <<= 1;
		delay_10us(1);
		
		// 保持 SDA 上的数据不变， 用于发送
		IIC_SCL = 1;
		delay_10us(1);
		
		// 2- 可以开始进行下一次发送
		IIC_SCL = 0;
		delay_10us(1);
	}
	
	// ???
	// 准备第一位数据 (先发送高位数据)
	//IIC_SDA = 1; // ????
	//delay_10us(1); // ??
}

/** 主机等待从从机发送过来的 ASK(应答) 信号 0 **/
void iic_wait_ask(){
	// 保存 SDA 上数据不变，为了让主机读取从机发来的信号 0/1
	IIC_SCL = 1;
	delay_10us(1);
	// 等待正确 ASK 信号 SDA=0 (从机收到XX)
	while(IIC_SDA){
		;
	}
	// 2-开始下一次的发送/接受，当前写数据，实际是发送                    
	IIC_SCL = 0;
	delay_10us(1);
}

















































