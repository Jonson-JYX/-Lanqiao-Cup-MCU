#include <STC15F2K60S2.H>
#include "Onewire.h"
#include "Timer.h"

unsigned char temp_value = 0;   //测量温度值
unsigned char temp_dat = 30;    //温度参数
bit temp_flag = 0;              //温度标志位

unsigned char Read_Temp(){
    unsigned int temp = 0;
    unsigned char low,high; 
    init_ds18b20();
    Write_DS18B20(0xCC);   //跳过ROM
    Write_DS18B20(0x44);   //开始转换
    Delay_OneWire(800);    //等待转换完成
    init_ds18b20();
    Write_DS18B20(0xCC);   //跳过ROM
    Write_DS18B20(0xBE);   //读取温度寄存器
    low = Read_DS18B20();   //读取温度值
    high = Read_DS18B20();   //读取温度值
    temp = (high << 8) | low;
    return temp * 0.0625f;   //转换为摄氏度
}

void Temp_login(){
    if(temp_cnt >= 200){
        temp_cnt = 0;
        temp_value = Read_Temp();
    }
    
    if(temp_value >= temp_dat){
        temp_flag = 1;
    }
    else{
        temp_flag = 0;
    }
}