#ifndef __24C02_H__
#define __24C02_H__

/********************（函数定义）********************/
//AT24C02指定地址写数据
void at24c02_write_one_byte(u8 addr,u8 dat);
//AT24C02指定地址读数据
u8 at24c02_read_one_byte(u8 addr);
#endif