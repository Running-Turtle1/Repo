//main.c中只需要包含共同头文件即可
#include "public.h"

u16 ms_trigger_count=0;
u8 save_value=0;
u8 save_buf[3]=0;

void main()
{
	//EEPROM应用
	u8 key_value=0;

	//STEP_MOTOR应用
	//默认逆时针方向:步进电机转动方向
	u8 dir=0;
	u8 step=0;

	leds_show_init();
	lcd1602_init();
	//初始化定时器0，定时时间1ms
	time1_1ms_init();


	//smg_1_2_display(5,0);
	/*
	lcd1602_show_data(0,0,'9');
	lcd1602_show_data(2,0,'a');
	lcd1602_show_data(15,0,'>');
	lcd1602_show_string(0,1,lcd1602_table);
	*/

	while(1)
   	{	
		//smg_1_2_refresh();	
		smg_1_2_display(5,save_buf[0]);
		smg_1_2_refresh();
		smg_1_2_display(6,save_buf[1]);
		smg_1_2_refresh();
		smg_1_2_display(7,save_buf[2]);
		smg_1_2_refresh();
		save_buf[0]=save_value/100;
		save_buf[1]=save_value%100/10;
		save_buf[2]=save_value%100%10;
		
		//======================
		key_value=key_scan();
		//save_value+1
		if(key_value==KEY1_PRESS)
		{
			save_value++;
			if(save_value==255)
			{
				save_value=0;
			}
		}
		//save_value清零
		else if(key_value==KEY2_PRESS)
		{
			save_value=0;	
		}
		//K3——写入EEPROM
		else if(key_value==KEY3_PRESS)
		{
			at24c02_write_one_byte(EEPROM_ADDRESS,save_value);
		}
		//K4——读出EEPROM
		else if(key_value==KEY4_PRESS)
		{
			save_value=at24c02_read_one_byte(EEPROM_ADDRESS);
		}	

	}
}

/*（步进电机）
	
		step_motor_8_beat_send_pulse(dir,step++);
		if(step==8)step=0;
		step_motor_4_beat_send_pulse(dir,step++);
		if(step>=4)step=0;		
		//转动速度尽量不要超过5ms,不然速度太慢了，不便于观察	
		delay_10us(500);
*/

/*******************************
* 函 数 名       : ex_int0()
* 函数功能		 : 中断服务程序
* 输    入       : 无
* 输    出    	 : 无
*******************************/
void time1_isr()	interrupt 3
{
	ms_trigger_count++;
	if(ms_trigger_count>=1000)
	{
		//==========================
		//save_value++;
		ms_trigger_count=0;
		LED_D1=!LED_D1;
	}
	//需要重新赋值
	TH1=0xFC;
	TL1=0x18;
}
   		

