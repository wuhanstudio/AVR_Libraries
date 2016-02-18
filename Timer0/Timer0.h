/*
 * Timer0.h
 *
 * Created: 2016/2/17 10:26:03
 *  Author: WuhanStudio
 */ 

#include <avr/interrupt.h>

#ifndef TIMER0_H_
#define TIMER0_H_

void TC0_init()
{
	SREG = 0x80;    // 开总中断
	TIMSK = 0x01;   // 开T/C0溢出中断
	TCNT0 = 99;		// 初值
	TCCR0 = 0x05;	// T/C0预分频比1/1024
}

ISR(TIMER0_OVF_vect)
{
	TCNT0 = 99;
	// 终端程序
}

#endif /* TIMER0_H_ */