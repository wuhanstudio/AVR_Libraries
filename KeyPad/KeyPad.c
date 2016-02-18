/*
 * KeyPad.c
 *
 * Created: 2016/2/17 9:00:26
 *  Author: WuhanStudio
 */ 
#include "KeyPad.h"

void Key_init()
{
	KEY_DDR = 0X0F;
}

/**
	获取矩阵键盘按键值
**/
unsigned char KeyValue()
{
    unsigned char i,j,getSta,keyVal;
    
    for(i=0;i<4;i++)              
    {                  
        KEY_PORT = setSta_[i];
        _delay_us(50);       
        if(KEY_PIN!=setSta_[i])
        {
            getSta=KEY_PIN&0xf0;
            for(j=0;j<4;j++)    
                if(getSta==getSta_[j])                                 
             {
                    keyVal=j+i*4;
                    return keyVal;
             }
        }
    }
    return 0xFF;
}