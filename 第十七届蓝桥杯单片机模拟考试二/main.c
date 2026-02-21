#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "IIC.h"
#include "PCF8591.h"
#include "Onewire.h"
#include "DS18B20.h"
#include "KEY.h"
#include "LED.h"
#include "LED_Display.h"

void Init_MCU(){
    LED(0xFF);
    COM(0xFF);
    BUZ(0x00);
    SEG(0xFF);
}

void main(){
    Init_MCU();
    while(1){
        Key_Logic();
        LED_Login();
        Detection_Change();
        Temp_Change();
        Light_Change();
        LED_Display_Choose();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
    }
}