#include <STC15F2K60S2.H>
#include "IIC.h"
#include "Timer.h"

unsigned char light_value = 0;    //光照强度值
unsigned char light_level = 0;    //光照等级值  

unsigned char Read_Light(void){
    unsigned char Light= 0;    //光照强度值
    I2CStart();                 //发送起始信号
    I2CSendByte(0x90);         //发送器件地址+写命令
    I2CWaitAck();              //等待应答
    I2CSendByte(0x01);         //发送控制字节
    I2CWaitAck();              //等待应答
    I2CStop();                  //发送停止信号

    I2CStart();                 //发送起始信号
    I2CSendByte(0x91);         //发送器件地址+读命令
    I2CWaitAck();              //等待应答
    Light = I2CReceiveByte();  //读取数据
    I2CWaitAck();              //等待应答
    I2CStop();                  //发送停止信号
    return Light;        //返回光照强度值
}

void Light_login(){
    if(light_cnt >= 200){
        light_cnt = 0;     //计数值清零
        light_value = Read_Light();    //读取光照强度值
        if(light_value >= 153){
            light_level = 1;   //光照等级1
        }
        else if(light_value >= 102 && light_value < 153){
            light_level = 2;   //光照等级2
        }
        else if(light_value >= 26 && light_value < 102){
            light_level = 3;   //光照等级3
        }
        else if(light_value < 26){
            light_level = 4;   //光照等级4
        }
    }
}