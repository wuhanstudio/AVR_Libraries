/*
 * ADC.h
 *
 * Created: 2016/2/17 16:36:01
 *  Author: WuhanStudio
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char AH,AL;

void ADC_init();
float ADC_Convert();

#endif /* ADC_H_ */