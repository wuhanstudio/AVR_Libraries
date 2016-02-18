/*
 * LCD1602.c
 *
 * Created: 2016/2/17 8:42:03
 *  Author: WuhanStudio
 */ 
#include "LCD1602.h"

/**
	LCD1602写入数据
**/
void LCD_write_data(unsigned char data) 
{
	RS_SET;
	RW_CLR;
	EN_SET;
	Data_IO = data;
	_delay_ms(5);
	EN_CLR;
}

/**
	LCD1602写入命令
**/
void LCD_write_com(unsigned char com) 
{	
	RS_CLR;
	RW_CLR;
	EN_SET;
	Data_IO = com;
	_delay_ms(5);
	EN_CLR;
}

/**
	LCD1602初始化
**/
void LCD_init(void) 
{
	Data_IO = 0xFF;				       //电平设置
	Data_DDR = 0xFF;				   //方向输出
	PORTA = 0xFF;                      //电平设置
	DDRA = 0xFF;                       //方向输出，1602液晶控制线端口设置	
	
	LCD_write_com(0x38);				//显示模式设置
	_delay_ms(5);
	LCD_write_com(0x08);				//显示关闭
	_delay_ms(5);
    LCD_write_com(0x01);				//显示清屏
	_delay_ms(5);
    LCD_write_com(0x06);				//显示光标移动设置
	_delay_ms(5);
	LCD_write_com(0x0C);				//显示开及光标设置
    _delay_ms(5);
}

/**
	LCD1602清屏
**/
void LCD_clear(void) 
{
	LCD_write_com(0x01);
	_delay_ms(5);
}

/**
	LCD1602显示一个字符
**/
void LCD_write_char(unsigned char x,unsigned char y,char data) 
{
    if (y == 0) 
    	LCD_write_com(0x80 + x);
    else 
    	LCD_write_com(0xC0 + x);
    LCD_write_data(data);  
}

/**
	LCD1602显示一个字符串
**/
void LCD_write_str(unsigned char x,unsigned char y,char *s) 
{	
    if (y == 0) 
    	LCD_write_com(0x80 + x);
    else 
    	LCD_write_com(0xC0 + x);    
    while (*s) 
    {
    	LCD_write_data( *s);
    	s ++;
    }
}