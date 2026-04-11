#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Sound.h"
#include "Timer.h"
#include "PCF8591.h"

unsigned int Temp_value = 0;   //温度值

unsigned int Read_Temp(){
    unsigned int temp;
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
    temp = (high << 8) + low;
    return temp * 0.0625f;   
}

void Temp_login(){
    if(Temp_cnt >= 200){
        Temp_value = Read_Temp();
        Sound_speed = (unsigned int)(330.0 + 0.6 * (float)Temp_value);
        RB2_VC = (unsigned int)(0.04 * (float)Temp_value * (float)Temp_value - 10.0 * (float)Temp_value + 255.0);
        Temp_cnt = 0;
    }
}