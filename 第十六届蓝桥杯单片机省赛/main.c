#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "IIC.h"
#include "Onewire.h"
#include "DS18B20.h"
#include "PCF8591.h"
#include "Timer.h"
#include "LED.h"
#include "LED_Display.h"
#include "KEY.h"
#include "Sound.h"
#include "Relay.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    LED(0xFF);
    Timer0_Init();
}

void main(){
    Init_MCU();
    while(1){
        Temp_login();
        Light_login();
        Sound_login();
        Key_login();
        Relay_login();
        LED_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}