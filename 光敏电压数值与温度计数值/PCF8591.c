#include <stc15f2k60s2.h>
#include "IIC.h"

float Lighting_Value(){
	float lighting_value;
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x01);
	I2CWaitAck();
	I2CStop();
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();
	lighting_value = I2CReceiveByte();
	I2CWaitAck();
	I2CStop();
	
	return lighting_value / 255;
}