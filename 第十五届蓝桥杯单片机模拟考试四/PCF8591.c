#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"
#include "NE555.h"

unsigned char DAC_value = 0;

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
    if(DAC_cnt >= 20){
        if(NE555_value < 200){
            DAC_value = 25;
        }
        else if(NE555_value > 2000){
            DAC_value = 230;
        }
        else{
            DAC_value = (unsigned char)((41.0 / 360.0) * (float)NE555_value + (20.0 / 9.0));
        }
        DAC_cnt = 0;
    }
}