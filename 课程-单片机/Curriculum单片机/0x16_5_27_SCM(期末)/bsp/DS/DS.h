#ifndef __DS_H__
#define __DS_H__


void ds1302_init();
void ds1302_read_time();
void ds1302_write_byte(u8 addr,u8 dat);
u8 ds1302_read_byte(u8 addr);
 
#endif