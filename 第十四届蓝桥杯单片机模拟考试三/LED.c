#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Common.h"
#include "PCF8591.h"
#include "DS18B20.h"
#include "Timer.h"
#include "Uart.h"

unsigned char LED_value = 0xFF;
bit LED_flag = 0;

void LED_login(){
    unsigned char dat = S5_cnt % 2;
    if(S4_flag == 0){
        LED_value = 0xFE;
    }
    else{
        LED_value = 0xFF;
        switch(dat){
            case 0:
                LED_value = 0xFD;
                break;
            case 1:
                LED_value = 0xFB;
                break;
        }
        if(Temp_value > 260 || Temp_value < 200){
            LED_value &= 0xDF;
        }
        else{
            LED_value |= 0xF9;
        }
        if(Uart_flag){
            LED_flag = 1;
            LED_cnt = 0;
        }
        if(LED_flag){
            LED_value &= 0x7F;
            if(LED_cnt >= 3000){
                LED_cnt = 0;
                LED_flag = 0;
                LED_value |= 0x80;
            }
        }
    }
    LED(LED_value);
}