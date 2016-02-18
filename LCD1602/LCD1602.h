/*
 * LCD1602.h
 *
 * Created: 2016/2/17 8:42:13
 *  Author: WuhanStudio
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

#ifndef LCD1602_H_
#define LCD1602_H_
#define RS_CLR	PORTA &= ~(1 << PA5)        //RS置低
#define RS_SET	PORTA |= (1 << PA5)         //RS置高

#define RW_CLR	PORTA &= ~(1 << PA4)        //RW置低
#define RW_SET	PORTA |= (1 << PA4)         //RW置高

#define EN_CLR	PORTA &= ~(1 << PA3)        //E置低
#define EN_SET	PORTA |= (1 << PA3)         //E置高

#define Data_IO	        PORTC       		//液晶数据口
#define Data_DDR        DDRC        		//数据口方向寄存器

void LCD_write_com(unsigned char com);
void LCD_write_data(unsigned char data);

void LCD_init(void);
void LCD_clear(void);
void LCD_write_char(unsigned char x,unsigned char y,char data);
void LCD_write_str(unsigned char x,unsigned char y,char *s);

#endif /* LCD1602_H_ */