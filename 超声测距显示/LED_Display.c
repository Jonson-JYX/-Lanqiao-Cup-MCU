#include <stc15f2k60s2.h>
#include "Common.h"
#include "Delay.h"
#include "UItrasound.h"

code unsigned char SEG_Table[] = {
	0xC0,	//0
	0xF9,	//1
	0xA4,	//2
	0xB0,	//3
	0x99,	//4
	0x92,	//5
	0x82,	//6
	0xF8,	//7
	0x80,	//8
	0x90,	//9
	0xFF	//È«Ãð
};

unsigned char dat_arr[] = {10,10,10,10,10,10,10,10};
unsigned char dat1 = 0;
void dat_Change(){
	if(time == 199){
		dat1 = Uitrasound_Value();
		dat_arr[5] = dat1 / 100;
		dat_arr[6] = dat1 % 100 / 10;
		dat_arr[7] = dat1 % 10;
	}
}

void LED_Display_Show(){
	unsigned char dat;
	unsigned char com;
	for(com = 0;com < 8;com++){
		SEG(0xFF);
		COM(1<<com);
		dat = SEG_Table[dat_arr[com]];
		if(com == 5){
			dat &= 0x7F;
		}
		SEG(dat);
		Delay50us();
	}
	SEG(0xFF);
	COM(0xFF);
}