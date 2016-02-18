/*
 * EEPROM.c
 *
 * Created: 2016/2/16 14:21:32
 *  Author: WuhanStudio
 */ 
#include <avr/io.h>
#include "EEPROM.h"
char read_char_eeprom(unsigned int EPADD)
{
	while((EECR&0x02)==1);  // 等待上一次写操作结束
	EEAR = EPADD;			// 设置地址
	EECR |= 0x01;			// 启动读操作
	return EEDR;
}

void write_char_eeprom(unsigned int EPADD,char EPDATA)
{
	while((EECR&0x02)==1); // 等待上一次写操作结束
	EEAR = EPADD;		   // 设置地址	
	EEDR = EPDATA;		   // 设置数据
	EECR |= 0x04;		   // 打开写使能
	EECR |= 0x02;          // 启动写操作
}

char * read_str_eeprom(unsigned int EPADD,unsigned int length)
{
	if(length==0) length = 50;
	unsigned int count = 0;	
	char temp[length];
	DATA = temp;
	
	while(read_char_eeprom(EPADD)!='\0'&& count<length)
	{
		temp[count] = read_char_eeprom(EPADD);				
		count++;
		EPADD++;
	}
	temp[count] = '\0';
	return DATA;
}

void write_str_eeprom(unsigned int EPADD,char* EPDATA)
{
	while(*EPDATA!='\0')
	{ 
		write_char_eeprom(EPADD,*EPDATA);
		EPADD++;
		EPDATA++;	
		_delay_ms(10);
	}
}