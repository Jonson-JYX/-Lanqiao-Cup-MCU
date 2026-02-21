#include <stc15f2k60s2.h>
#include "DELAY.h"

void Delay(unsigned char time)		//@12.000MHz
{
	unsigned char i, j;
	while(time--){
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}