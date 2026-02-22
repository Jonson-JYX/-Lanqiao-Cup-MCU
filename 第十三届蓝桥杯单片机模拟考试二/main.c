#include <STC15F2K60S2.H>
#include "Common.h"
#include "EEPROM.h"
#include "PCF8591.h"
#include "LED_Display.h"
#include "LED.h"
#include "KEY.h"
#include "Timer.h"
#include "Delay.h"

void Init_MCU(){
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    LED(0xFF);
    Timer0_Init();
}

void main(){
	Read_EEPROM(EEPROM_value,0,1);
	count = EEPROM_value[0];
    Init_MCU();
    while(1){
        Key_login();
        DAC_login();
        LED_login();
        LED_Display_Choose();
        LED_Display_Show();
        LED_Display_Show();
        LED_Display_Show();
    }
}