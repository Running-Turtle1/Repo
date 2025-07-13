#ifndef __GUI_H
#define __GUI_H

#include "stm32f10x.h"
#include "lcd_driver.h"

/* 编译选择 */
//#define USE_FONT_UPDATE                   //使用字库更新函数
//#define USE_FLASH_CHAR                    //使用FLASH字库

/* 字库文件地址 */
#define GUI_ASCII_FILE  "图片/ASCII（8X16）.DZK"
#define GUI_12CHAR_FILE "图片/12号字体（16X16）.DZK"
#define GUI_16CHAR_FILE "图片/16号字体（24X21）.DZK"

/* 设置字库地址 */
#define GUI_FLASH_ASCII_ADDR     6112846  //ASCII字库首地址（6114304 - 1456 - 2）
#define GUI_FLASH_12CHAR_ADDR    6114304  //12号字库首地址（6880386 - 766080 - 2）
#define GUI_FLASH_16CHAR_ADDR    6880386  //16号字库首地址（8388608 - 1508220 - 2）

/* 更新字库选择项 */
#define GUI_UPDATE_ASCII         0x01     
#define GUI_UPDATE_12CHAR        0x02
#define GUI_UPDATE_16CHAR        0x04
#define GUI_UPDATE_ALL           0x07

/* 声明全局变量 */
void GUI_Dot(uint16_t x, uint16_t y, uint16_t color);
void GUI_BigPoint(uint16_t x, uint16_t y, uint16_t color);
void GUI_Box(uint16_t xState, uint16_t yState, uint16_t xEnd, uint16_t yEnd, uint16_t color);
void GUI_DrowSign(uint16_t x, uint16_t y, uint16_t color);

void GUI_FontUpdate(uint8_t updateState);
void GUI_Show12ASCII(uint16_t x, uint16_t y, uint8_t *p, 
                     uint16_t wordColor, uint16_t backColor);
void GUI_Show12Char(uint16_t x, uint16_t y, uint8_t *ch, 
                    uint16_t wordColor, uint16_t backColor);
void GUI_Show16Chinese(uint16_t x, uint16_t y, uint8_t *cn, 
                       uint16_t  wordColor, uint16_t backColor);

#endif
