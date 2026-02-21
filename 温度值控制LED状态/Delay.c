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


