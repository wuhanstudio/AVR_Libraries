/*
 * EEPROM.h
 *
 * Created: 2016/2/16 14:36:10
 *  Author: WuhanStudio
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define F_CPU 16000000UL
#include <util/delay.h>

/**
	从指定的EEPROM地址处读出一个字节
**/
char read_char_eeprom(unsigned int EPADD);

/**
	从指定的EEPROM地址处写入一个字节
**/
void write_char_eeprom(unsigned int EPADD, char EPDATA);

/**
	从指定的EEPROM地址处写入一个字符串
**/
char * read_str_eeprom(unsigned int EPADD,unsigned int length);

/**
	从指定的EEPROM地址处读出一个字符串
**/
void write_str_eeprom(unsigned int EPADD,char* EPDATA);

char * DATA;
#endif /* EEPROM_H_ */