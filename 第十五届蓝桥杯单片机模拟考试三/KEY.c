#include <STC15F2K60S2.H>
#include "Delay.h"
#include "PCF8591.h"

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;
unsigned char Parameter_min = 10;
unsigned char Parameter_max = 60;
unsigned char num = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //S4
        Delay100ms();
        while(P44 == 0){
           key = 1;
        }
    }
    if(P42 == 0){   //S8
        Delay100ms();
        while(P42 == 0){
            key = 2;
        }
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){   //S5
        Delay100ms();
        while(P44 == 0){
           key = 3;
        }
    }
    if(P42 == 0){   //S9
        Delay100ms();
        while(P42 == 0){
            key = 4;
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    switch(key){
        case 1:
            S4_cnt = (S4_cnt + 1) % 3;
            if(S4_cnt % 3 != 1){
                S5_cnt = 0;
            }
            break;
        case 2:
            if(S5_cnt % 2 == 0 && S4_cnt % 3 == 1){
                if(Parameter_min < 50){
                 Parameter_min += 10;
                }
            }
            if(S5_cnt % 2 == 1 && S4_cnt % 3 == 1){
                if(ADC_value >= 0.0 && ADC_value < 1.0){
                    Parameter_min = 0;
                }
                else if(ADC_value >= 1.0 && ADC_value < 2.0){
                    Parameter_min = 10;
                }
                else if(ADC_value >= 2.0 && ADC_value < 3.0){
                    Parameter_min = 20;
                }
                else if(ADC_value >= 3.0 && ADC_value < 4.0){
                    Parameter_min = 30;
                }
                else if(ADC_value >= 4.0 && ADC_value <= 5.0){
                    Parameter_min = 40;
                }
            }
            break;
        case 3:
            if(S4_cnt % 3 == 1){
                S5_cnt = (S5_cnt + 1) % 2;
            }
            if(S4_cnt % 3 == 2){
                num = 0;
            }
            break;
        case 4:
            if(S5_cnt % 2 == 0 && S4_cnt % 3 == 1){
                if(Parameter_max < 90){
                    Parameter_max += 10;
                }
            }
            if(S5_cnt % 2 == 1 && S4_cnt % 3 == 1){
                if(ADC_value >= 0.0 && ADC_value < 1.0){
                    Parameter_max = 50;
                }
                else if(ADC_value >= 1.0 && ADC_value < 2.0){
                    Parameter_max = 60;
                }
                else if(ADC_value >= 2.0 && ADC_value < 3.0){
                    Parameter_max = 70;
                }
                else if(ADC_value >= 3.0 && ADC_value < 4.0){
                    Parameter_max = 80;
                }
                else if(ADC_value >= 4.0 && ADC_value <= 5.0){
                    Parameter_max = 90;
                }
            }
            break;
    }
}