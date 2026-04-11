#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Timer.h"

unsigned int Temp_value = 0;

unsigned int Read_Temp(){
    unsigned int temp = 0;
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
    return (unsigned int)((float)temp * 0.625f);
}

void Temp_login(){
    if(Temp_cnt >= 200){
        Temp_value = Read_Temp();
        Temp_cnt = 0;
    }
}