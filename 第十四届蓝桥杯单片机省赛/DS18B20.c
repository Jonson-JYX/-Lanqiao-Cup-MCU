#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Timer.h"

unsigned int Temp_value = 0;
unsigned int xdata Temp_Average = 0;
unsigned int xdata Temp_num = 0;
unsigned int xdata Temp_sum = 0;
unsigned int Temp_max = 0;
unsigned int Temp_dat = 30;

float Read_Temp(){
    float temp = 0;
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
     if(Temp_flag && Collect_Flag == 0){
        float temp = Read_Temp();
        Temp_value = (unsigned int)(temp * 10.0);
        Temp_sum += Temp_value;
        Temp_num ++;
        Temp_Average = Temp_sum / Temp_num;
        if((unsigned int)temp > Temp_max){
            Temp_max = (unsigned int)temp;
        }
        Temp_flag = 0;
    }
}