/*
 * Digitron.c
 *
 * Created: 2016/2/18 9:16:13
 *  Author: WuhanStudio
 */ 
#include "Digitron.h"

//********计数值处理函数******************//
void LED_process(unsigned int i,unsigned char *p)
{
	p[0]=i/1000;//千位
	p[1]=i/100%10;//百位
	p[2]=i/10%10;//十位
	p[3]=i%10;//个位
}

//**********动态显示函数,参数p为待显示的数组名**********//
void LED_display(unsigned char *p)
{
	unsigned char i,sel=0x01;//低位:0x01高位:0x10
	LED_DDR_SEL=0x0f;//低位:0x0f高位:0xf0
	LED_DDR_DATA=0xff;
	for (i=0;i<4;i++)
	{
		LED_SEL=sel;//PA为位选,共阳:LED_SEL=sel;共阴:LED_SEL=~sel;
		LED_DATA=~LED_table[p[i]];
		//字型表,共阳:LED_DATA=~LED_table[p[i]];共阴:LED_DATA=LED_table[p[i]];
		_delay_ms(2);
		sel=sel<<1;
	}
}

//**********数码管初始化函数**********/
/*
void LED_init(void)
{
	LED_SEL|=0x0f;
	LED_DDR_SEL|=0x0f;
}
*/

//**********数码管显示调用函数**********//
void LED(unsigned int i)
{
	LED_process(i,LED_dp);
	LED_display(LED_dp);

}