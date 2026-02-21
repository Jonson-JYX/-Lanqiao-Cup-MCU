#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Timer.h"

unsigned int temp_value;

float Read_temp(){
    unsigned int temp;
    unsigned char low,high;
    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0x44);
    Delay_OneWire(800);
    init_ds18b20();
    Write_DS18B20(0xCC);
    Write_DS18B20(0xBE);
    low = Read_DS18B20();
    high = Read_DS18B20();
    temp = (high << 8) | low;
    return (float)temp * 0.0625;
}

void Temp_login(){
    float dat = Read_temp();
    if(temp_cnt >= 500){
        temp_cnt = 0;
        temp_value = (unsigned int)(dat * 10.0);
    }
}