#include <stc15f2k60s2.h>
#include "IIC.h"

float Lighting_Value(){
	float Lighting_Dat;
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x01);
	I2CWaitAck();
	I2CStop();
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();
	Lighting_Dat = I2CReceiveByte();
	I2CWaitAck();
	I2CStop();
	
	return Lighting_Dat / 255.0;
}