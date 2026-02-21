#include <stc15f2k60s2.h>
#include "delay.h"
#include "intrins.h" 

//定义延时函数100微秒
void Delay100us()		//@12.000MHz
{
	unsigned char i;

	_nop_();
	i = 47;
	while (--i);
}

void Delay20ms()		//@12.000MHz
{
	unsigned char i, j;

	i = 39;
	j = 230;
	do
	{
		while (--j);
	} while (--i);
}

