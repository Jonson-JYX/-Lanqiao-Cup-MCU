#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Timer.h"

unsigned int temp_value = 0;

float Read_Temp(){
    unsigned int dat;
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
    dat = (high << 8) | low;
    return (float)dat * 0.0625;
}

void Temp_login(){
    float dat = Read_Temp();
    if(Temp_cnt >= 500){
        Temp_cnt = 0;
        temp_value = (unsigned int)(dat * 10.0);
    }
}