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
    double DAC_dat = 0.0;
    if(NE555_now >= 0){
        if(NE555_now <= 500){
            DAC_dat = 51.0;
        }
        else if(NE555_now > 500 && NE555_now <= NE555_PF){
            DAC_dat = (204.0 / (NE555_PF - 500.0)) * NE555_now + 102000.0 / (NE555_PF - 500.0) - 51.0;
        }
        else{
            DAC_dat = 255.0;
        }
    }
    else{
        DAC_dat = 0.0;
    }
    Read_DAC((unsigned char)DAC_dat);
}