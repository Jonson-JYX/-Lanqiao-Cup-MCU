#include <STC15F2K60S2.H>
#include "IIC.h"

unsigned char ADC_value = 0;
unsigned char Read_ADC(){
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
    return dat;
}

void ADC_login(){
    unsigned char dat = Read_ADC();
    if(dat <= 51){
        ADC_value = 10;
    }
    else if(dat >= 204){
        ADC_value = 90;
    }
    else{
        ADC_value = (unsigned char)((float)dat * 80.0 / 153.0 - 50.0 / 3.0);
    }
}