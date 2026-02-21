#include <stc15f2k60s2.h>
#include "intrins.h"

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

void Delay200us(void)	//@12.000MHz
{
	unsigned char data i, j;

	i = 3;
	j = 82;
	do
	{
		while (--j);
	} while (--i);
}

void Delay50us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 147;
	while (--i);
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

void Delay1ms(void)	//@12.000MHz
{
	unsigned char data i, j;

	i = 12;
	j = 169;
	do
	{
		while (--j);
	} while (--i);
}

