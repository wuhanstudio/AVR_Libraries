/*
 * PWM.h
 *
 * Created: 2016/2/17 9:34:31
 *  Author: WuhanStudio
 */ 


#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>

void PWM_init();
void PWM(unsigned int value);

#endif /* PWM_H_ */