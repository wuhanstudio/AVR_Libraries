/*
 * DS1820.h
 *
 * Created: 2016/2/18 8:55:40
 *  Author: WuhanStudio
 */ 


#ifndef DS1820_H_
#define DS1820_H_
#include "avr/io.h"
#define F_CPU 16000000UL
#include <util/delay.h>

//DS18B20控制端口定义，连接在PF3脚
#define DQ_IN	        DDRF &= ~(1 << PF3)		//设置输入，DS18B20接单片机PF3口
#define DQ_OUT	        DDRF |= (1 << PF3)		//设置输出
#define DQ_CLR	        PORTF &= ~(1 << PF3)	//置低电平
#define DQ_SET	        PORTF |= (1 << PF3)		//置高电平
#define DQ_R	        PINF & (1 << PF3)		//读电平

unsigned char DS18B20_Reset();                //初始化和复位

unsigned char DS18B20_read_byte();
void DS18B20_write_byte(unsigned char value);

void DS18B20_start();
unsigned int DS18B20_read_temp();
void data_do(unsigned int temp_d);

#endif /* DS1820_H_ */