#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Uart.h"
#include "EEPROM.h"

sbit S4 = P3^3;

unsigned char num = 0;
unsigned char Key_Scan(){
    unsigned char key = 0;
    if(S4 == 0){
        Delay100ms();
        while(S4 == 0){
            key = 1;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    if(key == 1){
        Send_EEPROM();
    }
}

void Reset_Count_Inc(){
    num++;                // 复位次数+1
    EEPROM_value[0] = num;// 赋值到EEPROM缓存数组
    Write_EEPROM(EEPROM_value, 0, 1); // 写入EEPROM地址0
}