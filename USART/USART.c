/*
 * USART.c
 *
 * Created: 2016/2/16 16:20:07
 *  Author: WuhanStudio
 */ 
#include <avr/io.h>
#include "USART.h"

/**
	串口初始化函数
**/
void USART_init()
{
  UCSR0A=0x00;                                 //单倍速模式 
  UCSR0B=0x18;                                 //接收中断允许，发送结束和寄存器空中断关闭，采用查询发送模式
  UCSR0C=0x86;                                 //异步串口，无校验位，1停止位，8数据位                                
  UCSR0C=(1<<UCSZ01)|(1<<UCSZ00);              //写UCSRC寄存器,异步通信无校验，8位数据1位停止位 
  UBRR0H=BAUDRATE_H;                           //写波特率的值 
  UBRR0L=BAUDRATE_L; 
}

/**
	串口读取一个字符
**/
char read_char_USART()
{
	char TEMP = -1;
	while((UCSR0A&0x80)!=0x80);
	TEMP = UDR0;	
	return TEMP;
}

/**
	串口发送一个字符
**/
void send_char_USART(char DATA)
{
	while(!(UCSR0A&(1<<UDRE0)));		//等待发送寄存器空
	UDR0=DATA;							//写入发送数据
	while(!(UCSR0A&(1<<TXC0)));			//等待发送完毕
	UCSR0A|=(1<<TXC0);
}

/**
	串口读取一个字符串
**/
char * read_str_USART(unsigned int length)
{
	if(length==0) length = 50;
	
	unsigned int count = 0;	
	char TEMP[length];	
	uDATA = TEMP;
	
	char READ = read_char_USART();	
	while(READ!=' ' && count<length)
	{
		TEMP[count] = READ;
		count++;
		READ = read_char_USART();
	}
	TEMP[count] = '\0';
	
	return uDATA;
}

/**
	串口发送一个字符串
**/
void send_str_USART(char * DATA)
{
	while(*DATA!='\0')
	{
		send_char_USART(*DATA);
		DATA++;
	}
}