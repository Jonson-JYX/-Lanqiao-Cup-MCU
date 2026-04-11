#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

unsigned char Light_dat = 61;   //设置光线临界值
unsigned char Light_value = 0;  //实时光线
bit Light_flag = 0;

unsigned char Read_Light(){
    unsigned char light = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x01);
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
        if(Light_dat > Light_value){
            Light_flag = 1;
        }
        else{
            Light_flag = 0;
        }
    }
}