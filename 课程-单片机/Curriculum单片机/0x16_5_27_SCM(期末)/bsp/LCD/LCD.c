#include "public.h"

/*******************************************************************************
* 函 数 名       : lcd1602_write_cmd
* 函数功能		 : LCD1602写命令
* 输    入       : cmd：指令
* 输    出    	 : 无

*******************************************************************************/
void lcd1602_write_cmd(u8 cmd)
{
	// 可以查询 lcd1602 时序图的 写时序来进行编码
	LCD1602_RS=0;//选择命令
	LCD1602_RW=0;//选择写
	LCD1602_E=0;
	LCD1602_DATAPORT=cmd;//准备命令
	delay_10us(100);
	LCD1602_E=1;//使能脚E先上升沿写入
	delay_10us(100);
	LCD1602_E=0;//使能脚E后负跳变完成写入	
}

/*******************************************************************************
* 函 数 名       : lcd1602_write_data
* 函数功能		 : LCD1602写数据
* 输    入       : dat：数据
* 输    出    	 : 无
*******************************************************************************/

void lcd1602_write_data(u8 dat) 
{
	LCD1602_RS=1;//选择数据
	LCD1602_RW=0;//选择写
	LCD1602_E=0;
	LCD1602_DATAPORT=dat;//准备数据
	delay_10us(100);
	LCD1602_E=1;//使能脚E先上升沿写入
	delay_10us(100);
	LCD1602_E=0;//使能脚E后负跳变完成写入		
}

/*******************************************************************************
* 函 数 名       : lcd1602_init
* 函数功能		 : LCD1602初始化
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/

void lcd1602_init()
{
	lcd1602_write_cmd(0x38);//数据总线8位，显示2行，5*7点阵/字符
	lcd1602_write_cmd(0x0c);//显示功能开，无光标，光标闪烁
	lcd1602_write_cmd(0x06);//写入新数据后光标右移，显示屏不移动
	lcd1602_write_cmd(0x01);//清屏	
}

/*******************************************************************************
* 函 数 名       : lcd1602_clear
* 函数功能		 : LCD1602清屏
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/
void lcd1602_clear()
{
	lcd1602_write_cmd(0x01);	
}

/*******************************************************************************
* 函 数 名       : lcd1602_show_string
* 函数功能		 : LCD1602显示字符
* 输    入       : x,y：显示坐标，x=0~15，y=0~1;
				   str：显示字符串
* 输    出    	 : 无
*******************************************************************************/
void lcd1602_show_string(u8 x,u8 y,u8 *str)
{
	u8 i=0;

	if(y>1||x>15)return;//行列参数不对则强制退出

	if(y<1)	//第1行显示
	{	
		while(*str!='\0')//字符串是以'\0'结尾，只要前面有内容就显示
		{
			if(i<16-x)//如果字符长度超过第一行显示范围，则在第二行继续显示
			{
				lcd1602_write_cmd(0x80+i+x);//第一行显示地址设置	
			}
			else
			{
				lcd1602_write_cmd(0x40+0x80+i+x-16);//第二行显示地址设置	
			}
			lcd1602_write_data(*str);//显示内容
			str++;//指针递增
			i++;	
		}	
	}
	else	//第2行显示
	{
		while(*str!='\0')
		{
			if(i<16-x) //如果字符长度超过第二行显示范围，则在第一行继续显示
			{
				lcd1602_write_cmd(0x80+0x40+i+x);	
			}
			else
			{
				lcd1602_write_cmd(0x80+i+x-16);	
			}
			lcd1602_write_data(*str);
			str++;
			i++;	
		}	
	}				
}

/*LCD1602 显示DS1302日期和时间 函数*/
//---秒分时日月周年 最低位读写位;-------//
//u8 gREAD_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; 
// u8 gDS1302_TIME[7] = {0x01, 0x19, 0x20, 0x21, 0x05, 0x24, 0x20};
// //---DS1302时钟初始化2021年05月20日星期四13点51分47秒。---//
//---存储顺序是秒分时日月周年,存储格式是用BCD码---//
// u8 gDS1302_TIME[7] = {0x47, 0x51, 0x13, 0x20, 0x04, 0x05, 0x21};
int temperture; // 温度;
u8 i=0;
void LcdDisplay(){
	lcd1602_write_cmd(0x80+0X40); // 这条指令的作用是将LCD1602的光标移动到第二行的第一个字符位置。
	lcd1602_write_data('0'+gDS1302_TIME[2]/16);				//时
	lcd1602_write_data('0'+(gDS1302_TIME[2]&0x0f));				 
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[1]/16);				//分
	lcd1602_write_data('0'+(gDS1302_TIME[1]&0x0f));	
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[0]/16);				//秒
	lcd1602_write_data('0'+(gDS1302_TIME[0]&0x0f));

	lcd1602_write_cmd(0x80); // 将光标移动到第一行的第一个字符位置
	lcd1602_write_data('2');			//年
	lcd1602_write_data('0');
	lcd1602_write_data('0'+gDS1302_TIME[6]/16);			 
	lcd1602_write_data('0'+(gDS1302_TIME[6]&0x0f));
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[4]/16);			//月
	lcd1602_write_data('0'+(gDS1302_TIME[4]&0x0f));
	lcd1602_write_data('-');
	lcd1602_write_data('0'+gDS1302_TIME[3]/16);			//日
	lcd1602_write_data('0'+(gDS1302_TIME[3]&0x0f));
	
	lcd1602_write_data(' ');
	if((gDS1302_TIME[5]&0x07) == 1){
		lcd1602_write_data('M');
		lcd1602_write_data('o');
		lcd1602_write_data('n');
	}
	else if((gDS1302_TIME[5]&0x07) == 2){
		lcd1602_write_data('T');
		lcd1602_write_data('u');
		lcd1602_write_data('e');
		lcd1602_write_data('s');
	}
	else if((gDS1302_TIME[5]&0x07) == 3){
		lcd1602_write_data('W');
		lcd1602_write_data('e');
		lcd1602_write_data('d');
		lcd1602_write_data('n');
	}
	else if((gDS1302_TIME[5]&0x07) == 4){
		lcd1602_write_data('T');
		lcd1602_write_data('h');
		lcd1602_write_data('u');
		lcd1602_write_data('r');
	}
	else if((gDS1302_TIME[5]&0x07) == 5){
		lcd1602_write_data('F');
		lcd1602_write_data('r');
		lcd1602_write_data('i');
	}
	else if((gDS1302_TIME[5]&0x07) == 6){
		lcd1602_write_data('S');
		lcd1602_write_data('a');
		lcd1602_write_data('t');
	}
	else{
		lcd1602_write_data('S');
		lcd1602_write_data('u');
		lcd1602_write_data('n');
	}
	//lcd1602_write_cmd(0x8f); // 0x8? , 其中 ? 代表第 ? 个位置显示什么, ? = [0, f]
	//lcd1602_write_data('0'+(gDS1302_TIME[5]&0x07));	//星期
	
		i++;
        if(i%50==0){
        //间隔一段时间读取温度值，间隔时间要大于温度传感器转换温度时间
            temperture=ds18b20_read_temperture()*10;//保留温度值小数后一位
            
        }
		lcd1602_write_cmd(0x89 + 0x40); // 第 9 个开始写
        
        
    //  lcd1602_write_data('0' + (int)temp_value%10); //百位
        
        if(temperture<0)//负温度
        {
            temperture=-temperture;
            lcd1602_write_data('-'); //百位
        }
        else{
             
        }
        
        
        lcd1602_write_data('0' + temperture/1000); //百位
        lcd1602_write_data('0' + temperture%1000/100); //十位
        lcd1602_write_data('0' + temperture%1000%100/10); //个位+小数点
        lcd1602_write_data('.');
        lcd1602_write_data('0' + temperture%1000%100%10); //小数点后一位
//      lcd1602_write_data('0' + temp_value%10); //小数点后两位
}

