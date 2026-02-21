#include <STC15F2K60S2.H>
#include "KEY.h"
#include "DS18B20.h"
#include "Common.h"

code unsigned char LED_Table[] = {0xFE,0xFD,0xFB,0xF7};

//LED逻辑函数
void LED_login(){
    float temp_value = Temp_Value();
    unsigned int temp = (unsigned int)temp_value;
    if(temp > Temp_max){
        LED(LED_Table[0]);
    }
    if(temp >= Temp_min && temp <= Temp_max){
        LED(LED_Table[1]);
    }
    if(temp < Temp_min){
        LED(LED_Table[2]);
    }
    if(Temporarily_max < Temporarily_min){
        LED(LED_Table[3]);
    }
}