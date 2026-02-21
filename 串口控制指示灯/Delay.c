#include "stc15f2k60s2.h"
#include "intrins.h"

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
