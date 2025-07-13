/* 下载程序后，指示灯D1闪烁表示程序正常运行，按键K_UP设定CAN模式，按键K_DOWN发送
	，发送数据是0-7字节，大小是0-7.CAN波特率选择500Kbps*/

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "button.h"
#include "lcd_driver.h"
#include "gui.h"
#include "can.h"

 
void lcd_display()	   //LCD初始化显示
{
	TFT_ClearScreen(BLACK);
	GUI_Show12ASCII(10,10,"PRECHIN",GREEN,BLACK);
	GUI_Show12ASCII(10,30,"www.prechin.com",GREEN,BLACK);
	GUI_Show12ASCII(10,50,"CAN Test! Buand:500Kbps",GREEN,BLACK);	
	GUI_Show12ASCII(10,70,"2015-11-7",GREEN,BLACK);
	GUI_Show12ASCII(10,90,"K_UP:MODE  K_DOWN:Send",GREEN,BLACK);
	GUI_Show12ASCII(10,120,"Mode:",GREEN,BLACK); 
	GUI_Show12ASCII(50,120,"CAN_Mode_LoopBack",RED,BLACK); //环回模式
	GUI_Show12ASCII(10,150,"Send Data:",GREEN,BLACK);
	GUI_Show12ASCII(10,180,"Receive Data:",GREEN,BLACK);

}
void data_pros()	//数据处理函数
{
	u8 key,i,res;
	u8 cantxbuf[8],charbuf[9],canrebuf[8];
	static u8 mode=CAN_Mode_LoopBack;	 //CAN_Mode_LoopBack=1,	CAN_Mode_Normal=0
	key=keyscan(0);
	if(key==K_UP_PRESS)	  //模式切换
	{
		mode=!mode;
		if(mode)GUI_Show12ASCII(50,120,"CAN_Mode_LoopBack",RED,BLACK); //环回模式
		else GUI_Show12ASCII(50,120,"CAN_Mode_Normal   ",RED,BLACK); //环回模式			
		GUI_Show12ASCII(90,150,"                     ",RED,BLACK);
		GUI_Show12ASCII(114,180,"                    ",RED,BLACK);
		CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,mode);	//切换后模式初始化 500Kbps
					
	}
	if(key==K_DOWN_PRESS)	  //发送
	{
		for(i=0;i<8;i++)
		{
			cantxbuf[i]=i;	//给canbuf数组赋初值
			charbuf[i]=cantxbuf[i]+0x30;		
		}
		charbuf[8]='\0';
		GUI_Show12ASCII(90,150,charbuf,RED,BLACK);	
		res=Can_Send_Msg(cantxbuf,8);//发送8个字节 
		if(res)
		{
			GUI_Show12ASCII(170,150,"Failed ",RED,BLACK);	
		}
		else
		{
			GUI_Show12ASCII(170,150,"Success",RED,BLACK);	
		}
			
	}
	key=Can_Receive_Msg(canrebuf); 
	if(key)	 //如果返回值不等于0 表示有数据接收
	{
		for(i=0;i<key;i++)
		{
			charbuf[i]=canrebuf[i]+0x30;	
		}
		charbuf[8]='\0';
		GUI_Show12ASCII(114,180,charbuf,RED,BLACK);				
	}
}

int main(void)
{	
	u8 i=0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	TFT_Init();	
	led_init();
	button_init();
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_LoopBack);	//初始化环回模式 500Kbps
	lcd_display();

	while(1)
	{	
		data_pros();
		i++;
		if(i==15)
		{
			i=0;
			led0=~led0;
		}
		delay_ms(10);					
	}	
}
