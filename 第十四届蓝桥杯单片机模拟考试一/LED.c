#include <stc15f2k60s2.h>
#include "KEY.h"
#include "PCF8591.h"
#include "Common.h"
#include "Timer.h"
bit LED1 = 0;
bit LED2 = 0;

void LED_logic(){
    if(S12_cnt % 2 == 0){
        if(Sound_value <= Decibel_value * 10){
            LED(0xFE);
        }
        if(Sound_value > Decibel_value *10){         
            if(LED_cnt1 == 99){
                if(LED1 == 0){
                    LED(0x7E); 
                    LED1 = 1;
                } else {
                    LED(0xFE); 
                    LED1 = 0;
                }
            }
        }
    }
    if(S12_cnt % 2 == 1){
        if(Sound_value <= Decibel_value * 10){
            LED(0xFD);
        }
        if(Sound_value > Decibel_value *10){         
            if(LED_cnt2 == 99){
                if(LED2 == 0){
                    LED(0x7D);
                    LED2 = 1;
                } else {
                    LED(0xFD); 
                    LED2 = 0;
                }
            }
        }
    }
}