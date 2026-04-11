#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"
#include "NE555.h"
#include "DS18B20.h"
#include "DS1302.h"

unsigned char Light_value = 0;
unsigned char xdata Light_Standard = 0;

unsigned char Read_Light(){
    unsigned char light = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x03);
    I2CWaitAck();
    I2CStop();
    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    light = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();
    return light;
}

void Light_login(){
    if(Light_cnt >= 100){
        Light_value = Read_Light();
        Light_cnt = 0;
    }
    if(Light_Standard > Light_value){
        light_flag = 1;
        NE555_flag = 1;
        Temp_flag = 1;

        if(Collect_Flag == 0){
            Temp_value = (unsigned int)(Read_Temp() * 10.0);  
            NE555_value = (TH0 << 8) | TL0;                  
            Time_value = ReadRTC();                          
            Collect_Flag = 1;  
            TH0 = 0; 
            TL0 = 0;
        }
    }
    else{
        light_flag = 0;
    }
}