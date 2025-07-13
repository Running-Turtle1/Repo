#include "public.h"

int temp_value; // 全部变量记录温度

void main(){	
	ds18b20_init();// 初始化DS18B20温度传感器
	lcd1602_init(); // LCD 1602 初始化
	T0_50ms_init(); // T0 50 ms 中断配置
	
	while(1){
		lcd1602_write_cmd(0x80); // 第一行开始写
		
		if(temp_value<0)//处理负温度
		{
			temp_value=-temp_value; // 转化成正数
			lcd1602_write_data('-'); // 输出 - 号
		
		}
		
		// 输出显示温度信息
		// 输出显示 Temperature 的缩写 temp
		lcd1602_write_data('T');
		lcd1602_write_data('E');
		lcd1602_write_data('M');
		lcd1602_write_data('P');
		lcd1602_write_data(':');
		lcd1602_write_data('0' + temp_value/1000); // 温度的十位
		lcd1602_write_data('0' + temp_value%1000/100); // 温度个位
		lcd1602_write_data('.'); // 小数点
		lcd1602_write_data('0' + temp_value%100/10); // 保留小数点一位
		lcd1602_write_data('0' + temp_value%10); // 保留小数点两位
		// \' 转义字符与下面的句子结合 输出 'C 表示摄氏度
		lcd1602_write_data('\''); 
		lcd1602_write_data('C');
		// 显示个人信息
		lcd1602_show_string(0, 1, "CREATED BY WPC"); // 显示个人信息
	}
	
}

// 定时器配置 :  1s 读取一次温度
void T0_isr() interrupt 1{
	static unsigned int counter = 0; // 记录中断次数
	counter ++; // 中断次数 + 1
	if(counter == 20){ // 50ms * 20 = 1000 ms = 1 s
		counter = 0; // 清空记录变量
		temp_value=ds18b20_read_temperture()*100;// 全局变量 temp_value 读取温度, 保留温度值小数后两位
	}
	// 保证 50ms 的计时器中断周期 : 65536-50*1000 = 15536 = 0x3CB0
	TH0 = 0x3C;
	TL0 = 0xB0;
}