#include <stc15f2k60s2.h>
#include "intrins.h"

void Delay500ms(void)	//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 23;
	j = 205;
	k = 120;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay10ms(void)	//@12.000MHz
{
	unsigned char data i, j;

	i = 117;
	j = 184;
	do
	{
		while (--j);
	} while (--i);
}

