#include <stc15f2k60s2.h>
#include "IIC.h"

float RB2_Value(){
	float RB2_value;
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x03);
	I2CWaitAck();
	I2CStop();
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();
	RB2_value = I2CReceiveByte();
	I2CWaitAck();
	I2CStop();
	
	return RB2_value / 255.0;
}