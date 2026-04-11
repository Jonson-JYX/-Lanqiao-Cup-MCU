#include <STC15F2K60S2.H>
#include "Common.h"
#include "Delay.h"
#include "NE555.h"
#include "PCF8591.h"
#include "Ultrasound.h"
#include "KEY.h"
#include "LED.h"
#include "Relay.h"
#include "EEPROM.h"
#include "LED_Display.h"
#include "Timer.h"

void Init_MCU(){
    LED(0xFF);
    SEG(0xFF);
    COM(0xFF);
    BUZ(0x00);
    REY(0x00);
    Timer0_Init();
    Timer1_Init();
    NE555_cnt = 0;
    Sound_cnt = 0;
    DAC_cnt = 0;
    ADC_cnt = 0;
    LED1_cnt = 0;
    LED2_cnt = 0;
    LED3_cnt = 0;
}

void main(){
    Init_MCU();
    Read_EEPROM(EEPROM_value,0,1);
    Relay_num = EEPROM_value[0];
    while(1){
        Key_login();
        NE555_login();
        ADC_login();
        DAC_login();
        Sound_login();
        LED_login();
        Relay_login();
        LED_Display_Choose();
        LED_Display_Show();
    }
}