#include <STC15F2K60S2.H>
#include "PCF8591.h"
#include "DS18B20.h"
#include "KEY.h"
#include "Common.h"

code unsigned char LED_Table[] = {
    0xFE,0x7E,0xFD,0x7D
};

//LED逻辑函数
void LED_Login(){
    float Temp_value = Temp_Value();
    float Light_value = RB2_Value();
    unsigned int temp_dat = (unsigned int)(Temp_value);
    unsigned int light_dat = (unsigned int)(Light_value * 4900.0 / 47.0 + 1000.0 / 47.0);
    if(S4_cnt % 2 == 0){
        if(temp_dat > Temp_dat && light_dat > Light_dat){
            LED(LED_Table[1]);
        }
        else{
            LED(LED_Table[0]);
        }
    }
    if(S4_cnt % 2 != 0){
        if(temp_dat > Temp_dat && light_dat > Light_dat){
            LED(LED_Table[3]);
        }
        else{
            LED(LED_Table[2]);
        }
    }
}