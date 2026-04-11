#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"
#include "DS18B20.h"

unsigned int RB2_value = 0;
unsigned int Light_value = 0;
unsigned int DAC_value = 0;

float Read_RB2(){
    unsigned char RB2 = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x01);
    I2CWaitAck();
    I2CStop();

    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    RB2 = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();

    return (float)RB2 * 5.0 / 255.0;
}

float Read_Light(){
    unsigned char Light = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x03);
    I2CWaitAck();
    I2CStop();

    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    Light = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();

    return (float)Light * 5.0 / 255.0;
}

void Read_DAC(unsigned char u){
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x40);
	I2CWaitAck();
	I2CSendByte(u);
	I2CStop();
}

void RB2_login(){
    if(RB2_cnt >= 200){
        RB2_value = (unsigned int)(Read_RB2() * 100.0);
        RB2_cnt = 0;
    }
}

void Light_login(){
    if(Light_cnt >= 200){
        Light_value = (unsigned int)(Read_Light() * 100.0);
        Light_cnt = 0;
    }
}

void DAC_login(){
    if(DAC_cnt >= 200){
        if(Temp_value <= 15){
            DAC_value = 51;
        }
        else if(Temp_value >= 45){
            DAC_value = 204;
        }
        else{
            DAC_value = (unsigned int)(5.1 * (float)Temp_value - 24.6);
        }
        DAC_cnt = 0;
        Read_DAC(DAC_value);
    }
}