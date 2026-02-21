#include <stc15f2k60s2.h>
#include "IIC.h"

float ADC_Value(){
	float ADC_dat;
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x03);
	I2CWaitAck();
	I2CStop();
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();
	ADC_dat = I2CReceiveByte();
	I2CWaitAck();
	I2CStop();
	
	return ADC_dat / 255.0;
}