#include <STC15F2K60S2.H>
#include "IIC.h"
#include "KEY.h"

unsigned int xdata RB2_value = 0;
unsigned int xdata Light_value = 0;
unsigned int xdata RB2_dat = 0;

unsigned char Read_RB2(){
    unsigned char xdata RB2 = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x03);
    I2CWaitAck();
    I2CStop();

    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    RB2 = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();
    return RB2;
}

unsigned char Read_Light(){
    unsigned char Light = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x01);
    I2CWaitAck();
    I2CStop();
    
    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    Light = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();
    return Light;
}

void RB2_login(){
    if(S4_cnt == 2 && S5_cnt == 1){
        RB2_value = (unsigned int)((float)Read_RB2() * 5.0 / 255.0 * 100.0);
    }
}
    

void Light_login(){
    if(S4_cnt == 2 && S5_cnt == 0){
        Light_value = (unsigned int)((float)Read_Light() * 5.0 / 255.0 * 100.0);
    }
}