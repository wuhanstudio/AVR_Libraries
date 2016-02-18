/*
 * ADC.c
 *
 * Created: 2016/2/17 16:36:09
 *  Author: WuhanStudio
 */ 

#include "ADC.h"

void ADC_init()
{
	ADMUX = 0x40;			   // 结果右对齐，AVCC为基准电压，*通道0*
	ADCSRA = 0xA7;			   // 128预分频，禁止中断，使能自动转换
	SFIOR = 0x00;		       // 连续转换模式
	_delay_ms(1);
	ADCSRA = ADCSRA | 0x40;   // 开启一次AD转换 
}

float ADC_Convert()
{
	float CVAL;
	unsigned int TEMP = 0;
	
	AL = ADCL;
	AH = ADCH;
	
	TEMP = TEMP|AH;
	TEMP = TEMP<<8;
	TEMP = TEMP|AL;
	
	CVAL = TEMP;				// 转换结果为0-1023
	CVAL = CVAL*5/1023*1000;
	
	return CVAL; 
}