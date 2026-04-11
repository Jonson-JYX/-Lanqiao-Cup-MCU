#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

unsigned int RB2_value = 0;
unsigned int RB2_VC = 0;   //RB2测量的校准值
unsigned int RB2_dat = 0;  //RB2参数

unsigned int Read_RB2(){
    unsigned int value;
    I2CStart();                //发送起始信号
    I2CSendByte(0x90);        //发送设备地址+写命
    I2CWaitAck();             //等待ACK
    I2CSendByte(0x03);        //发送寄存器地址
    I2CWaitAck();             //等待ACK
    I2CStop();                 //发送停止信号

    I2CStart();                //发送起始信号
    I2CSendByte(0x91);        //发送设备地址+读命
    I2CWaitAck();             //等待ACK
    value = I2CReceiveByte();  //接收数据
    I2CWaitAck();             //等待ACK
    I2CStop();                 //发送停止信号

    return (unsigned int)(((float)value * 5.0 / 255.0 + RB2_VC / 1000.0) * 10);   //根据校准值计算实际电压值
}

void RB2_login(){
    if(RB2_cnt >= 200){   //每200ms读取一次RB2值
        RB2_value = Read_RB2();
        if(RB2_value >= 0 && RB2_value < 10){
            RB2_dat = 0;
        }
        else if(RB2_value >= 10 && RB2_value < 20){
            RB2_dat = 5;
        }
        else if(RB2_value >= 20 && RB2_value < 40){
            RB2_dat = 10;
        }
        else if(RB2_value >= 40 && RB2_value < 50){
            RB2_dat = 15;
        }
        else if(RB2_value >= 50){
            RB2_dat = 20;
        }
        RB2_cnt = 0;   //重置计数器
    }
}