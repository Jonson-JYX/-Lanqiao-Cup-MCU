#include <stc15f2k60s2.h>
#include "intrins.h"

void Delay40us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 117;
	while (--i);
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

void Delay10us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 27;
	while (--i);
}

