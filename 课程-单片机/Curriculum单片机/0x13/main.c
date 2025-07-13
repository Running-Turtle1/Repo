#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;
/*
	IIC 协议, 应用在 EEPROM (AT24C02), IIC 总线上最多可以挂 8 个 AT24C02(256 * 8bit), 000 - 111
	每一个 EEPROM 上存储器 (0x00 - OxFF)

	1. 找到地址为 1010, (000) 的 AT24C02
	2. 找到这个 AT24C02 后, 在它的地址为 0x01 的存储器
	3. 向这个存储器内写入数据 0x0F
*/
/*
	addr : AT24C02 上寄存器的地址
*/
void at24c02_write_byte(u8 addr, u8 dat){
	// 01 - 启动IIC
	IIC_start();
	// 02 - 发送 7 位地址码 (1010,000) + 写信号 : 0
	IIC_write_byte(0xA0); ?
	// 03 - 主机等待接受从机发送的有效ASK信号
	IIC_wait_ask();
	// 04 - 发送 8 位 AT24C02 内部的寄存器地址（例如 : 0x01)
	IIC_write_byte(addr);
	// 05 - 主机等待接受从机发送的有效ASK信号
	IIC_wait_ask();
	// 06 - 发送 8 位数据 (例如 : 0x0F)
	IIC_write_byte(0x0F);
	// 07 - 主机等待接受从机发送的有效ASK信号
	IIC_wait_ask();
	// 08 - 停止 IIC
	IIC_stop();
}
u8 at24c02_read_byte(u8 addr){
	// 01 - 启动IIC
	IIC_start();
	// 02 - 发送 7 位地址码 (1010,000) + 写信号 : 0
	IIC_write_byte(0xA0); ?
	// 03 - 主机等待接受从机发送的有效ASK信号
	IIC_wait_ask();
	// 04 - 发送 8 位 AT24C02 内部的寄存器地址（例如 : 0x01)
	IIC_write_byte(addr);
	// 05 - 主机等待接受从机发送的有效ASK信号
	IIC_wait_ask();
	
	// 06 - 启动 IIC
	IIC_start();
	// 07 - 发送 7 位地址码 (1010,000) + 读信号 : 1
	IIC_write_byte(0xA1); 
	//
	u8 Value = IIC_read_byte();
	
	//
	IIC_stop();
	
	return smg_show_data;
}

void delay_10us(u16 x){
	while(x --);
}

void main(){

}
