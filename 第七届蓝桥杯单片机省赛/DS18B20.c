#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Timer.h"
#include "KEY.h"

unsigned char Temp_value = 0;
unsigned char Temp_dat[] = {0,0,0,0,0,0,0,0,0,0};
unsigned char Temp_num = 0;

float Read_Temp(){
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
    return (float)temp * 0.0625;
}

void Temp_login(){
    if(Temp_flag){
        if(Temp_cnt >= Time_setting * 1000){
            Temp_value = (unsigned char)(Read_Temp());
            Temp_dat[Temp_num] = Temp_value;
            Temp_num++;
            Temp_cnt = 0;
        }
    }
}