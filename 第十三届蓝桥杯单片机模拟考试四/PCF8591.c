#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

int ADC_value = 0;
int Vol_value1 = 0;
int Vol_value2 = 0;

float ADC_Read(){
    float value;
    I2CStart();
    I2CSendByte(0x90); // 发送器件地址+写命令
    I2CWaitAck();
    I2CSendByte(0x03); // 发送控制字节，选择通道0
    I2CWaitAck();
    I2CStop();
    I2CStart();
    I2CSendByte(0x91); // 发送器件地址+读命令
    I2CWaitAck();
    value = I2CReceiveByte(); // 读取高8位
    I2CWaitAck();
    I2CStop();
    return value;
}

void ADC_login(){
    float dat = ADC_Read();
    if(ADC_cnt == 49){
        ADC_value = (int)(dat);
        Vol_value1 = (int)(dat / 255.0 * 500.0);
        Vol_value2 = (int)(dat / 255.0 * 50.0);
    }
}