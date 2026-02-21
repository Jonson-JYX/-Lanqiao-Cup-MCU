#include "stc15f2k60s2.h"
#include "intrins.h"

void Delay50us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 147;
	while (--i);
}

void Delay50ms(void)	//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 3;
	j = 72;
	k = 161;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}
