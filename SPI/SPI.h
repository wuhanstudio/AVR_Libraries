/*
 * SPI.h
 *
 * Created: 2016/2/17 16:46:32
 *  Author: WuhanStudio
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#define  F_CPU 16000000UL
#include <util/delay.h>

#define SS_SET (PORTB=PORTB|0x10)	// 置位SS引脚
#define SS_CLR (PORTB=PORTB&0xEF)	// 清零SS引脚

unsigned char SPI_TEMP;

void SPI_init();
void tran_SPI(unsigned char DATA);
void write_char(unsigned char ADD,unsigned char SA_DATA);
unsigned char read_char(unsigned char ADD);

//void write_en();

#endif /* SPI_H_ */