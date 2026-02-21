#include <stc15f2k60s2.h>
#include "IIC.h"
#include "KEY.h"

void RB2_DA(unsigned char u){
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x40);
	I2CWaitAck();
	I2CSendByte(u);
	I2CStop();
}

void DA_Cout(){
	if(count % 6 == 0 && count != 0){
		RB2_DA(153);
	}
	else{
		RB2_DA(51);
	}
}