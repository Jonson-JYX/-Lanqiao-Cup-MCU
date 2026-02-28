#include <STC15F2K60S2.H>
#include "Delay.h"
#include "NE555.h"

unsigned char S4_cnt = 0;
unsigned char S5_cnt = 0;

unsigned char Key_Scan(){
    unsigned char key = 0;
    P33 = 0;P32 = 1;
    if(P44 == 0){   //S4
        Delay100ms();
        if(P44 == 0){
            key = 1;
            while(P44 == 0);
        }
    }
    if(P42 == 0){   //S8
        Delay100ms();
        if(P42 == 0){
            key = 2;
            while(P42 == 0);
        }
    }
    P33 = 1;P32 = 0;
    if(P44 == 0){   //S5
        Delay100ms();
        if(P44 == 0){
            key = 3;
            while(P44 == 0);
        }
    }
    if(P42 == 0){   //S9
        Delay100ms();
        if(P42 == 0){
            key = 4;
            while(P42 == 0);
        }
    }
    return key;
}

void Key_login(){
    unsigned char key = Key_Scan();
    unsigned char S5 = S5_cnt % 2;
    unsigned char S4 = S4_cnt % 4;
    switch(key){
        case 1:
            S4_cnt = (S4_cnt + 1) % 4;
            if(S4_cnt % 4 == 0 || S4_cnt % 4 == 2){
                S5_cnt = 0;
            }
            break;
        case 2:
            switch(S4){
                case 1:
                    switch(S5){
                        case 0: //S8 超限参数
                            if(NE555_Hyperparameter < 9000){
                                NE555_Hyperparameter += 1000;
                            }
                            break;
                        case 1: //S8 校准参数
                            if(NE555_Calibration < 900){
                                NE555_Calibration += 100;
                            }
                            break;
                    }
                    break;
            }
            break;
        case 3:
            switch(S4){
                case 1:
                    S5_cnt = (S5_cnt + 1) % 2;
                    break;
                case 3:
                    S5_cnt = (S5_cnt + 1) % 2;
                    break;
            }
            break;
        case 4:
            switch(S4){
                case 1:
                    switch(S5){
                        case 0: //S8 超限参数
                            if(NE555_Hyperparameter > 1000){
                                NE555_Hyperparameter -= 1000;
                            }
                            break;
                        case 1: //S8 校准参数
                            if(NE555_Calibration > -900){
                                NE555_Calibration -= 100;
                            }
                            break;
                    }
                    break;
            }
            break;
    }
}