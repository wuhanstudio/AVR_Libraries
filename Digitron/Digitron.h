/*
 * Digitron.h
 *
 * Created: 2016/2/18 9:16:24
 *  Author: WuhanStudio
 */ 


#ifndef DIGITRON_H_
#define DIGITRON_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

//-----------------端口设置----------------
//使用本驱动需要修改这里以及下面的显示函数中的共阴共阳设置
#define LED_SEL        PORTA
#define LED_DDR_SEL    DDRA
#define LED_DATA	   PORTB
#define LED_DDR_DATA   DDRB

//----------------------------------------
//数码管字型表，对应的是：0，1，2，3，4，5，6，7，8，9
unsigned char LED_table[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6f,0x7d,0x07,0x7f,0x6f};
unsigned char LED_dp[4]={0,0,0,0};//显示的初始值：0，0，0，0

void LED_process(unsigned int i,unsigned char *p);
void LED_display(unsigned char *p);
void LED(unsigned int i);


#endif /* DIGITRON_H_ */