#ifdef __LCD1602_H__
#define __LCD1602_H__

//º¯ÊýÉùÃ÷
void test();
void lcd1602_write_cmd(u8 cmd);
void lcd1602_write_data(u8 dat);
void lcd1602_init();
void lcd1602_clear();
void lcd1602_show_string(u8 x,u8 y,u8 *str);
//void lcd1602_init();
//void lcd1602_clear();
//void lcd1602_show_string(u8 x,u8 y,u8 *str);

#endif