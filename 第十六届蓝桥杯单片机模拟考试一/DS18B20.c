#include <STC15F2K60S2.H>
#include "Onewire.h"

int temp_now = 0;

float Temp_Value(){
    float temp_value;
    unsigned char high,low;
    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0x44);
    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0xBE);
    low = Read_DS18B20();
    high = Read_DS18B20();
    temp_value = (high<<8) | low;
    return temp_value * 0.0625;

}

void Read_Temp(){
    float temp = Temp_Value();
    temp_now = (int)(temp * 10);
}