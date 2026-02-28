#include <STC15F2K60S2.H>
#include "IIC.h"
#include "NE555.h"

void Read_DAC(unsigned char dat){
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x40);
    I2CWaitAck();
    I2CSendByte(dat);
    I2CStop();
}

void DAC_login(){
    float dat = 0.0;
    if(NE555_now <= 500){
        Read_DAC(51);
    }
    else if(NE555_now >= NE555_Hyperparameter)
    {
        Read_DAC(255);
    }
    else{
        dat = (204.0 / ((float)NE555_Hyperparameter - 500.0)) * (float)NE555_now + 51.0 - (204.0 * 500.0) / ((float)NE555_Hyperparameter - 500.0);
        Read_DAC((unsigned char)dat);
    }
}