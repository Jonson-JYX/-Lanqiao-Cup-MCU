#include <STC15F2K60S2.H>
#include "IIC.h"
#include "KEY.h"
#include "Timer.h"

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
	if(DAC_cnt >= 500){
		if(count % 5 == 0 && count != 0){
			Read_DAC(204);
		}
		else{
			Read_DAC(51);
		}
		DAC_cnt = 0;
	}
}