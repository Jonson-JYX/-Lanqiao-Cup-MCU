#include <STC15F2K60S2.H>
#include "IIC.h"
#include "NE555.h"
#include "Timer.h"

unsigned int Humidity_dat = 40; //湿度参数
unsigned int Humidity_value = 0;//湿度采集
unsigned char DAC_value = 0;
unsigned char ADC_value = 0;

void Read_DAC(unsigned char dat){
    unsigned char DAC = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x40);
    I2CWaitAck();
    I2CSendByte(dat);
    I2CStop();
}

unsigned char Read_ADC(){
    unsigned char ADC = 0;
    I2CStart();
    I2CSendByte(0x90);
    I2CWaitAck();
    I2CSendByte(0x03);
    I2CWaitAck();
    I2CStop();
    I2CStart();
    I2CSendByte(0x91);
    I2CWaitAck();
    ADC = I2CReceiveByte();
    I2CWaitAck();
    I2CStop();
    return ADC;
}

void DAC_login(){
    if(DAC_cnt >= 200){
        if(Humidity_value <= Humidity_dat){
            DAC_value = 51;
        }
        else if(Humidity_value >= Humidity_dat){
            DAC_value = 255;
        }
        else{
            DAC_value = (204.0 / (80.0 - (float)Humidity_dat)) * (float)(Humidity_value) + 255.0 - (204.0 * 80.0) / (80.0 - (float)Humidity_dat);
        }
        Read_DAC(DAC_value);
        DAC_cnt = 0;
    }
}

void ADC_login(){
    ADC_value = Read_ADC();
    if(ADC_cnt >= 200){
        Humidity_value = (unsigned int)((100.0 / 255.0) * (float)ADC_value);
        ADC_cnt = 0;
    }
}