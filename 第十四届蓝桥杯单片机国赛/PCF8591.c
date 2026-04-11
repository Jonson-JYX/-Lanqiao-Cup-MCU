#include <STC15F2K60S2.H>
#include "Timer.h"
#include "IIC.h"
#include "Ultrasound.h"

bit Output_flag = 0;    //输出标志位
unsigned char DAC_value = 0;
unsigned char DAC_dat = 10;

void Read_DAC(unsigned char dat){
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x40);
    I2CWaitAck();
    I2CSendByte(dat);
    I2CWaitAck();
    I2CStop();
}

void DAC_login(){
    if(Record_flag){
        if(DAC_cnt >= 6000){
            Record_flag = 0;
        }
        if(Sound_value <= 10){
            DAC_value = (unsigned char)((float)DAC_dat / 10.0 * 51.0);
        }
        else if(Sound_value >= 90){
            DAC_value = 255;
        }
        else{
            DAC_value = (unsigned char)((float)DAC_dat / 10.0 + (5.0 - (float)DAC_dat / 10.0) / 80.0 * ((float)Sound_value - 10.0));
        }
    }
    else{
        if(Output_flag){
            Read_DAC(DAC_value);
            Output_flag = 0;
        }
    }
}