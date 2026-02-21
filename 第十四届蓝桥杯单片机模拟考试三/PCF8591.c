#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"
#include "KEY.h"

unsigned int ADC_value = 0;

float Read_ADC(){
    unsigned char dat;
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
    return (float)dat / 255.0;
}

void ADC_login(){
    float dat = Read_ADC();
    if(ADC_cnt >= 500 && S4_flag == 1){
        ADC_cnt = 0;
        ADC_value = (unsigned int)(dat * 1000.0);
    }
}