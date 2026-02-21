#include <STC15F2K60S2.H>
#include "IIC.h"
#include "KEY.h"
#include "DS18B20.h"

void DAC_Value(unsigned int dat){
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x40);
    I2CWaitAck();
    I2CSendByte(dat);
    I2CStop();
}

//DAC逻辑函数
void DAC_login(){
    float temp_value = Temp_Value();
    unsigned int temp = (unsigned int)temp_value;
    if(temp > Temp_max){
        DAC_Value(204);
    }
    if(temp >= Temp_min && temp <= Temp_max){
        DAC_Value(153);
    }
    if(temp < Temp_min){
        DAC_Value(102);
    }
}