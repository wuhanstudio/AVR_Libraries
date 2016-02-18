/*
 * Infrared.c
 *
 * Created: 2016/2/18 9:05:25
 *  Author: WuhanStudio
 */ 

#include "Infrared.h"

//***********************************************************************
//			定义变量区
//***********************************************************************
uchar key;
uint temp_value;
uint temp,A;             		      	//定义的变量,显示数据处理
uchar code_value=0;
uchar key_code[4]; 
uint l,p;

//***********************************************************************
//			遥控器键码
//***********************************************************************

#define KEY_0     0x16                 //键0
#define KEY_1     0x0C                 //键1
#define KEY_2     0x18                 //键2
#define KEY_3     0x5E                 //键3
#define KEY_4     0x08                 //键4
#define KEY_5     0x1C                 //键5
#define KEY_6     0x5A                 //键6
#define KEY_7     0x42                 //键7
#define KEY_8     0x52                 //键8
#define KEY_9     0x4A                 //键9
#define KEY_POWER 0x45                 //电源
#define KEY_MODE  0x46                 //模式
#define KEY_SOUND 0x47                 //静音


//***********************************************************************
//			IO端口初始化
//***********************************************************************

void Infrared_init()
{
    RED_SET;
	RED_IN;
}

//*************************************************************************
//	    显示采集到的数据到LED灯
//*************************************************************************

void Display_Key(uint data_KEY)
{   
    //LED = data_KEY;      //键值显示到LED灯上，二进制的形式显示，只识别0~9
	//LCD_write_char(0x0e,1,0X30+data_KEY);
}

//*************************************************************************
//			遥控器键值赋功能值子程序
//*************************************************************************
 void Key_Icode(void)
 {
   switch(key_code[2])
   {
    case KEY_0:key=0;break;
	case KEY_1:key=1;break;
	case KEY_2:key=2;break;
	case KEY_3:key=3;break;
	case KEY_4:key=4;break;
	case KEY_5:key=5;break;
	case KEY_6:key=6;break;
	case KEY_7:key=7;break;
	case KEY_8:key=8;break;
	case KEY_9:key=9;break;
	default:key=10;break;
   }
 }

//*************************************************************************
//			遥控器解码子程序
//*************************************************************************

void Red_Code()
{
	uchar i,j,k = 0;
	for(i = 0;i < 19;i++)
	{
		_delay_us(400);           //延时400us
		if(RED_R)                //9ms内有高电平，则判断为干扰，退出处理程序
			return;
	}
	
	while(!RED_R);            //等待9ms低电平过去

	for(i=0;i<5;i++)          //是否连发码
	{
	  _delay_us(500);
	  if(!RED_R)
		 return;
	}

	while(RED_R);               //等待4.5ms高电平过去

	for(i = 0;i < 4;i++)        //接收4个字节的数据
	{
		for(j = 0;j < 8;j++)      //每个字节的数据8位
		{
			while(!RED_R);         //等待变高电平
			while(RED_R)           //计算高电平时间
			{
				_delay_us(100);
				k++;
				if(k >= 22)           //高电平时间过长，则退出处理程序
					return;              
			}
			code_value>>=1;        //接受一位数据
			if(k >= 8)
				code_value|=0x80;   	//高电平时间大于0.56，则为数据1
			k = 0;                  //计时清零
		}
		key_code[i]=code_value;  //四个字节的数据
	}
	
	Key_Icode();             //调用赋值函数
	Display_Key(key);        //显示按键值 
}