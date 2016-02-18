/*
 * Infrared.h
 *
 * Created: 2016/2/18 9:05:11
 *  Author: WuhanStudio
 */ 


#ifndef INFRARED_H_
#define INFRARED_H_
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#define uchar unsigned char
#define uint unsigned int

//红外一体化接收头1838控制端口定义，连接在PF2脚
#define RED_IN	        DDRF &= ~(1 << PF2)		//设置输入，红外接收头接单片机PF2口
#define RED_OUT	        DDRF |= (1 << PF2)		//设置输出
#define RED_CLR	        PORTF &= ~(1 << PF2)	//置低电平
#define RED_SET	        PORTF |= (1 << PF2)		//置高电平
#define RED_R	        (PINF & (1 << PF2))		//读电平

void Infrared_init();
void Display_Key(uint data_KEY);
void Key_Icode(void);
void Red_Code();



#endif /* INFRARED_H_ */