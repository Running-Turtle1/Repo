#include "public.h"

//字码数组保存到Flash中
//共阴极数码管显示0~F的段码数据
u8 code g_smg_duan_code[]={
   	//0 ,1	 ,2   ,3   ,4   ,5   ,6   ,7   ,8   ,9   
	0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
	//A ,B   ,C   ,D   ,E   ,F
	0x77,0x7c,0x39,0x5e,0x79,0x71};

/*************************************************
* 函 数 名: void SMG_1_2_refresh()
* 函数功能: 动态数码管显示
* 输    入: 无
* 输    出: 无
*************************************************/
void smg_1_2_refresh()
{
	//延时一段时间，等待显示稳定					  
	//10ms=10*100*10us，由10ms逐渐减少，观察效果
	//经过尝试，1ms=10*100us时，效果较正常
	delay_10us(100);
	//消影子，防止速度太快了，产生影子
	//SMG_A_2_DP_PORT=0x00;
}
/*************************************************
* 函 数 名: SMG_1_2_display
* 函数功能: 动态数码管显示
* 输    入: 无
* 输    出: 无
*************************************************/
void smg_1_2_display(u8 pos,u8 dat)
{
	//u8 i=0;
	//for(i=0;i<8;i++)
	{
	   	switch(pos)//位选
		{
			case 0: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 1: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 2: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 3: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
			case 4: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 5: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 6: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 7: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
		 }
		//传送段选数据
		SMG_A_2_DP_PORT=g_smg_duan_code[dat];
		//经过尝试，1ms=10*100us时，效果较正常
		//delay_10us(10);
		//消影子，防止速度太快了，产生影子
		//SMG_A_2_DP_PORT=0x00;	
		}
}

/*******************************************************************************
* 函 数 名       : smg_display
* 函数功能		 : 动态数码管显示
* 输    入       : dat：要显示的数据
				   pos：从左开始第几个位置开始显示，范围1-8
* 输    出    	 : 无
*******************************************************************************/
void smg_display(u8 dat[],u8 pos)
{
	u8 i=0;
	//pos_temp(0~7)
	u8 pos_temp=pos-1;

	for(i=pos_temp;i<8;i++)
	{
	   	switch(i)//位选
		{
			case 0: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 1: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 2: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 3: 
				SMG_1_2_LS_C=1;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
			case 4: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=1;
				break;
			case 5: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=1;
				SMG_1_2_LS_A=0;
				break;
			case 6: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=1;
				break;
			case 7: 
				SMG_1_2_LS_C=0;
				SMG_1_2_LS_B=0;
				SMG_1_2_LS_A=0;
				break;
		}
		//传送段选数据
		SMG_A_2_DP_PORT=g_smg_duan_code[dat[i-pos_temp]];
		//延时1ms时间，等待显示稳定
		delay_10us(100);
		//消影
		SMG_A_2_DP_PORT=0x00;
	}
}
