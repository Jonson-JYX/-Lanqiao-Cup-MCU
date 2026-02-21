#include <stc15f2k60s2.h>
#include "Onewire.h"

float Temp_Value(){
	unsigned char low,high;
	unsigned int temp;
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);
	Delay_OneWire(800);
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0xBE);
	low = Read_DS18B20();
	high = Read_DS18B20();
	temp = (high<<8) | low;
	return temp * 0.0625;
}