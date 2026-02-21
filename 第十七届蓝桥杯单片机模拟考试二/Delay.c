#include <stc15f2k60s2.h>
#include "intrins.h"

void Delay15us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 42;
	while (--i);
}

void Delay100ms(void)	//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 144;
	k = 71;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
