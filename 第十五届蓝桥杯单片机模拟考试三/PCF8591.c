#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

float ADC_value = 0;

float Read_ADC(){
    float dat = 0.0;
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

    return dat / 255.0 * 5.0;
}

void ADC_login(){
    float dat = Read_ADC();
    ADC_value = dat;
}
