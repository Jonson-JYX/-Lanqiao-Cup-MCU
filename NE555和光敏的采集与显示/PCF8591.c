#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

unsigned int Light_value = 0;

float Read_Light(){
    unsigned char dat;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x01);
    I2CWaitAck();
    I2CStop();
    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    dat = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();
    return (float)dat / 255.0;
}

void Light_login(){
    float dat = Read_Light();
    if(Light_cnt >= 100){
        Light_value = (unsigned int)(dat * 50.0);
    }
}