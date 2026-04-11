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
	if(Key_Down){
		Key_Down = 0;
		switch(Key_value){
			case 1:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 1;
				break;
			case 2:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 2;
				break;
			case 3:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 3;
				break;
			case 4:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 4;
				break;
			case 5:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 5;
				break;
			case 6:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 6;
				break;
			case 7:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 7;
				break;
			case 8:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 8;
				break;
			case 9:
				LED_dat_arr[6] = 10;
				LED_dat_arr[7] = 9;
				break;
			case 10:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 0;
				break;
			case 11:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 1;
				break;
			case 12:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 2;
				break;
			case 13:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 3;
				break;
			case 14:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 4;
				break;
			case 15:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 5;
				break;
			case 16:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 6;
				break;
		}
	}
	if(Key_Long){
		Key_Long = 0;
		switch(Key_value){
			case 17:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 7;
				break;
			case 18:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 8;
				break;
			case 19:
				LED_dat_arr[6] = 1;
				LED_dat_arr[7] = 9;
				break;
			case 20:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 0;
				break;
			case 21:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 1;
				break;
			case 22:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 2;
				break;
			case 23:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 3;
				break;
			case 24:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 4;
				break;
			case 25:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 5;
				break;
			case 26:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 6;
				break;
			case 27:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 7;
				break;
			case 28:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 8;
				break;
			case 29:
				LED_dat_arr[6] = 2;
				LED_dat_arr[7] = 9;
				break;
			case 30:
				LED_dat_arr[6] = 3;
				LED_dat_arr[7] = 0;
				break;
			case 31:
				LED_dat_arr[6] = 3;
				LED_dat_arr[7] = 1;
				break;
			case 32:
				LED_dat_arr[6] = 3;
				LED_dat_arr[7] = 2;
				break;
		}
	}
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