#include <stc15f2k60s2.h>
#include "KEY.h"
#include "LED_Display.h"
#include "PCF8591.h"
#include "Delay.h"
#include "Common.h"

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

unsigned char Key_dat[] = {10,10,10,10,10,10,10,10};

void Key_Change(){
	if(count >= 10 && count <= 99){
		Key_dat[6] = count / 10;
		Key_dat[7] = count % 10;
	}
	else if(count >= 0 && count <= 9){
		Key_dat[6] = 10;
		Key_dat[7] = count % 10;
	}
}

void LED_Display_Show(){
	unsigned char com;
	unsigned char dat;
	for(com = 0;com < 8;com++){
		SEG(0xFF);
		COM(1<<com);
		dat = SEG_Table[Key_dat[com]];
		SEG(dat);
		Delay50us();
	}
	SEG(0xFF);
	COM(0xFF);
}