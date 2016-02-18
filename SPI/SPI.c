/*
 * SPI.c
 *
 * Created: 2016/2/17 16:46:42
 *  Author: WuhanStudio
 */ 

#include "SPI.h"

void SPI_init()
{
	DDRB |= 0xF0;		// 将PB4-PB7设置为输出，MISO在主机模式下会自动配置成输入
	SPCR = 0x53;		// 高位在先，时钟速率 1/128 FOSC, SPI 模式 0
	SPSR = 0x00;		
}

void tran_SPI(unsigned char DATA)
{
	SPDR = DATA;				// 将值写入SPDR
	while((	SPSR&0X80)==0);		// 等待SPIF置1
	SPI_TEMP = SPDR;				// 读回SPDR中收到的数据，读操作清零SPIF位
}

void write_char(unsigned char ADD,unsigned char SA_DATA)
{
	SS_SET;					// 拉高片选
	_delay_us(2);
	tran_SPI(0x02);        // 写命令 101+ADD
	tran_SPI(0x80|ADD);	   // 10位的命令，要分两次写入
	tran_SPI(SA_DATA);	   // 写入数据
	SS_CLR;				   // 拉低片选，芯片内部开始烧写过程
	_delay_ms(5);
}

unsigned char read_char(unsigned char ADD)
{
	SS_SET;
	_delay_us(2);
	tran_SPI(0x03);		// 写命令 110+ADD
	tran_SPI(ADD);		// 10位命令，要分两次写入
	
	SPCR=0x57;
	tran_SPI(0x00);
	SPCR = 0x53;
	SS_CLR;
	
	return SPI_TEMP;
}

