#include <stc15f2k60s2.h>
#include "Delay.h"
#include "intrins.h"

void Delay100ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 195;
	j = 138;
	do
	{
		while (--j);
	} while (--i);
}


void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay500us()		//@12.000MHz
{
	unsigned char i, j;
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void Delay100us(void)	//@12.000MHz
{
	unsigned char data i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}
