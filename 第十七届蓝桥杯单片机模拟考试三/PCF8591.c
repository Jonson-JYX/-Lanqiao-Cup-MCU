#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

unsigned char Light_value = 0;
unsigned char ADC_value = 0;

unsigned char Read_Light(){
    unsigned char value = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x01);
    I2CWaitAck();
    I2CStop();
    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    value = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();
    return value;
}

unsigned char Read_ADC(){
    unsigned char value = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x03);
    I2CWaitAck();
    I2CStop();
    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    value = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();
    return value;
}

void Light_login(){
    if(Light_cnt >= 10){
        Light_value = Read_Light();
    }
}

void ADC_login(){
    if(ADC_cnt >= 10){
        ADC_value = Read_ADC();
    }
}