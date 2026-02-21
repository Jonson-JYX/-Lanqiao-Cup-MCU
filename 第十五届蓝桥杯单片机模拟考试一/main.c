#include "stc15f2k60s2.h"
#include "Common.h"
#include "Delay.h"
#include "DS1302.h"
#include "KEY.h"
#include "LED_Display.h"
#include "LED.h"
#include "E2PROM.h"

void Init_MCU(){
    I2C_Init();
	SetRTC();
	SEG(0xFF);
    COM(0xFF);
    LED(0xFF);
    BUZ(0x00);
}

void main(){
    Init_MCU();
    while(1){
        LED_Display_Show(); // À¢–¬œ‘ æ
    }
}