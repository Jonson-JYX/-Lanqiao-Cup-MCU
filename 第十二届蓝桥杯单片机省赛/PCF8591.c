#include <STC15F2K60S2.H>
#include "IIC.h"

void DAC_Value(unsigned char value){
    I2CStart();
    I2CWaitAck();
    I2CSendByte(0x40);
    I2CWaitAck();
    I2CSendByte(value);
    I2CStop();
}