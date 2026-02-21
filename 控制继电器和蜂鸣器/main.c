#include <stc15f2k60s2.h>
#include "Common.h"
#include "intrins.h"

void Init_MCU(){
	LED(0xFF);
	COM(0xFF);
	SEG(0xFF);
	BUZ(0x00);
}

void Delay1000ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 8;
	j = 154;
	k = 122;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main(){
	Init_MCU();
	while(1){
		BUZ(0xEF);
		Delay1000ms();
		BUZ(0x00);
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		BUZ(0xBF);
		Delay1000ms();
		BUZ(0x00);
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
		Delay1000ms();
	}
}