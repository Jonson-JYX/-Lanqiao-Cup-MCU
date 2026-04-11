#include <stc15f2k60s2.h>
#include "KEY.h"
#include "Common.h"
#include "intrins.h"

code unsigned char SEG_Table[] = {
	0xC0,
	0xF9,
	0xA4,
	0xB0,
	0x99,	
	0x92,
	0x82,
	0xF8,
	0x80,
	0x90,
	0xFF
};

void Delay50us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 147;
	while (--i);
}

unsigned char LED_dat_arr[] = {10,10,10,10,10,10,10,10};

void LED_Display_Choose(){
	LED_dat_arr[6] = Key_value / 10;
	LED_dat_arr[7] = Key_value % 10;
}

void LED_Display_Show(){
	unsigned char com;
	unsigned char dat;
	for(com = 0;com < 8;com ++){
		SEG(0xFF);
		COM(1<<com);
		dat = SEG_Table[LED_dat_arr[com]];
		SEG(dat);
		Delay50us();
	}
	SEG(0xFF);
	COM(0xFF);
}