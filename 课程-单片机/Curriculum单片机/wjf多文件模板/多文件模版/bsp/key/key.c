#include "public.h"

/*******************************************************************************
* 函 数 名       : key_scan
* 函数功能		 : 检测独立按键是否按下，按下则返回对应键值
* 输    入       : 无
* 输    出    	 : u8
*******************************************************************************/
u8 key_scan()
{
	//第1步：第1次检测：K1,K2,K3,K4是否按下
	if(KEY_K1==0||KEY_K2==0||KEY_K3==0||KEY_K4==0)
	{
		//第2步：软件去抖动：延时10ms=10×100*10us
		delay_10us(1000);
		//第3步：第2次检测：K1是否按下
		if(KEY_K1==0)
		{
			//第4步：等待K1按键松开,完成1次完整的按键操作
			while(KEY_K1==0);
			return KEY1_PRESS;
		}
		else if(KEY_K2==0)
		{
			//等待K2按键松开,完成2次完整的按键操作
			while(KEY_K2==0);
			return KEY2_PRESS;
		}
		else if(KEY_K3==0)
		{
			//等待K3按键松开,完成1次完整的按键操作
			while(KEY_K3==0);
			return KEY3_PRESS;
		}
		else if(KEY_K4==0)
		{
			//等待K4按键松开,完成1次完整的按键操作
			while(KEY_K4==0);
			return KEY4_PRESS;
		}		
	}
	else
		return KEY_UNPRESS;	
}

