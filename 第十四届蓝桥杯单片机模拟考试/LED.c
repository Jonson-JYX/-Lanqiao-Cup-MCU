#include <STC15F2K60S2.H>
#include "Common.h"
#include "Distance.h"
#include "KEY.h"
#include "Timer.h"

bit LED1 = 0;
bit LED2 = 0;

void LED_login(){
    if(S4_cnt % 2 == 0){
        if(sound_dat > sound_value){
            if(LED_cnt == 3){
                if(LED1 == 0){
                    LED(0xFA);
                    LED1 = 1;
                }
                else{
                    LED(0xFE);
                    LED1 = 0;
                }
            }
        }
        else{
            LED(0xFE);
        }
    }
    if(S4_cnt % 2 == 1){
        if(sound_dat > sound_value){
            if(LED_cnt == 3){
                if(LED2 == 0){
                    LED(0xF9);
                    LED2 = 1;
                }
                else{
                    LED(0xFD);
                    LED2 = 0;
                }
            }
        }
        else{
            LED(0xFD);
        }
    }
}