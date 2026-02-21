#include <stc15f2k60s2.h>
#include "Onewire.h"

float Temp_Value(){
	float temp_value;
	unsigned char high,low;
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0x44);
	Delay_OneWire(800);
	init_ds18b20();
	Write_DS18B20(0xCC);
	Write_DS18B20(0xBE);
	low = Read_DS18B20();
	high = Read_DS18B20();
	temp_value = (high<<8) | low;
	return temp_value * 0.0625;
}