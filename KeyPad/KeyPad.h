/*
 * KeyPad.h
 *
 * Created: 2016/2/17 9:00:40
 *  Author: WuhanStudio
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define KEY_DDR     DDRA
#define KEY_PORT    PORTA
#define KEY_PIN     PINA

/*--------------------------------------------------------------------
程序名称：4*4按键扫描程序
程序功能：键盘扫描
注意事项：
提示说明：
输    入：
返    回：
--------------------------------------------------------------------*/
/*
    K4-----K5-----K6-----K7
     |      |      |      |
    03H----02H----01H----00H －K0
    07H----06H----05H----04H －K1
    0BH----0AH----09H----08H －K2
    0FH----0EH----0DH----0CH －K3
*/
const unsigned char setSta_[4]={0xfe,0xfd,0xfb,0xf7};       
const unsigned char getSta_[4]={0x70,0xb0,0xd0,0xe0};  

void Key_init();
unsigned char KeyValue();

#endif /* KEYPAD_H_ */