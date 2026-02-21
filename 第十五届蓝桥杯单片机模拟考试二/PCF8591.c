#include <stc15f2k60s2.h>
#include "IIC.h"

//PCF8591的光敏电阻数据读取
unsigned char Photoresistor_Read(){
	unsigned char photoresistor_Value;
	I2CStart();
	I2CSendByte(0x90);
	I2CWaitAck();
	I2CSendByte(0x01);
	I2CWaitAck();
	I2CStop();
	
	I2CStart();
	I2CSendByte(0x91);
	I2CWaitAck();
	photoresistor_Value = I2CReceiveByte();
	I2CWaitAck();
	I2CStop();
	return photoresistor_Value;
}