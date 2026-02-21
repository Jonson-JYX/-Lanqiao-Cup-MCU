#include <STC15F2K60S2.H>
#include "INTRINS.H"

void Delay50us(void)	//@12.000MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	i = 147;
	while (--i);
}
