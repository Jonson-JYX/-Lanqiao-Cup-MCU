#include <STC15F2K60S2.H>
#include "Timer.h"
#include "IIC.h"

unsigned int ADC_value = 0;
unsigned int light_value = 0;

float Read_ADC(){
    unsigned char dat = 0;
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

    return dat / 255.0 * 500.0;
}

float Read_Light(){
    unsigned char dat = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x03);
    I2CWaitAck();
    I2CStop();

    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    dat = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();

    return dat / 255.0 * 500.0;
}

void ADC_login(){
    if(ADC_cnt >= 200){
        ADC_cnt = 0;
        ADC_value = Read_ADC();
    }
}

void Light_login(){
    if(light_cnt >= 200){
        light_cnt = 0;
        light_value = Read_Light();
    }
}