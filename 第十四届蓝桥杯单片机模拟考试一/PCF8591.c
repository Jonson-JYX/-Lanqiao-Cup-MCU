#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

unsigned int Sound_value = 0;

float RB2_Value(){
    float dat;
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
    return dat / 255.0 * 5.0 * 18.0;
}

void Read_Sound(){
    float dat = RB2_Value();
    Sound_value = (unsigned int)(dat * 10);
}