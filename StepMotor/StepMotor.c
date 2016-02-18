/*
 * StepMotor.c
 *
 * Created: 2016/2/18 9:22:13
 *  Author: WuhanStudio
 */ 

#include "StepMotor.h"
void StepMotor_init()
{
	DDRD |= 0xF0;
	LRCTRL = 1;
}

void StemMotor_driver()
{
	unsigned char x;
	if(LRCTRL==1)
	{
		for(x=0;x<8;x++)
		{
			PORTD = table_left[x];
			_delay_ms(1);
		}
	}
	
	if(LRCTRL==0)
	{
		for (x=0;x<8;x++)
		{
			PORTD = table_right[x];
			_delay_ms(1);
		}
	}
}
