#ifndef __IIC_H__
#define __IIC_H__

void iic_start();
void iic_stop();
void iic_write_byte(u8 dat);
void iic_wait_ask();
void iic_ack();
void iic_nack();


#endif