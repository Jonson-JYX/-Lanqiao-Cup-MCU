#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Timer.h"

unsigned int Temp_value = 0;
unsigned int Temp_dat = 25;

float Read_Temp(){
    float temp = 0.0;
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
    temp = (high << 8) | low;
    return (float)temp * 0.0625;
}

void Temp_login(){
    if(Temp_cnt >= 20){
        Temp_value = (unsigned int)(Read_Temp() * 10);
        Temp_cnt = 0;
    }
}