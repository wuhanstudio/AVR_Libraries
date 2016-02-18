/*
 * StepMotor.h
 *
 * Created: 2016/2/18 9:22:20
 *  Author: WuhanStudio
 */ 


#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char LRCTRL;														// 1:À≥ ±’Î 0:ƒÊ ±’Î
const char table_left[] = {0x90,0x80,0xc0,0x40,0x60,0x20,0x30,0x10};
const char table_right[] = {0x10,0x30,0x20,0x60,0x40,0xc0,0x80,0x90};

void StepMotor_init();
void StemMotor_driver();

#endif /* STEPMOTOR_H_ */