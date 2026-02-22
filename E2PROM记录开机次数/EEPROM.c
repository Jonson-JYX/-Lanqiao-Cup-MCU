#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Delay.h"

unsigned char EEPROM_value[1] = {0};

void Write_EEPROM(unsigned char *dat,unsigned char addr,unsigned char num){
    I2CStart();
    I2CSendByte(0xA0);
    I2CWaitAck();
    I2CSendByte(addr);
    I2CWaitAck();
    while(num--){
        I2CSendByte(*dat++);
        I2CWaitAck();
        I2C_Delay(200);
    }
    I2CStop();
    Delay50ms();
}

void Read_EEPROM(unsigned char *dat,unsigned char addr,unsigned char num){
    I2CStart();
    I2CSendByte(0xA0);
    I2CWaitAck();
    I2CSendByte(addr);
    I2CWaitAck();

    I2CStart();
    I2CSendByte(0xA1);
    I2CWaitAck();
    while(num--){
        *dat++ = I2CReceiveByte();
        if(num){
            I2CSendAck(0);
        }
        else{
            I2CSendAck(1);
        }
    }
    I2CStop();
}