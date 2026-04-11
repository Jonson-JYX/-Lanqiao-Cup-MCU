#include <STC15F2K60S2.H>
#include "Delay.h"
#include "Common.h"

bit Free_flag = 1;       //空闲标志位
bit Wait_flag = 0;       //等待标志位
bit Run_flag = 0;        //运行标志位
bit coordinate_flag = 0; //坐标接受标志位
bit Obstacle_flag = 0;   //障碍物标志物
unsigned char key_value = 0;
unsigned int Position_value[] = {0,0}; //坐标
unsigned char S8_cnt = 0;
unsigned char S9_cnt = 0;
unsigned int R_Parameter = 10;
int B_Parameter = 0;

void Key_Scan(){
    P44 = 0;P42 = 1;P35 = 1;
    if(P33 == 0){   //S4
        Delay100ms();
        if(P33 == 0){
            key_value = 1;
            while(P33 == 0);
        }
    }
    if(P32 == 0){   //S5
        Delay100ms();
        if(P32 == 0){
            key_value = 2;
            while(P32 == 0);
        }
    }

    P44 = 1;P42 = 0;P35 = 1;
    if(P33 == 0){   //S8
        Delay100ms();
        if(P33 == 0){
            key_value = 3;
            while(P33 == 0);
        }
    }
    if(P32 == 0){   //S9
        Delay100ms();
        if(P32 == 0){
            key_value = 4;
            while(P32 == 0);
        }
    }
    
    P44 = 1;P42 = 1;P35 = 0;
    if(P33 == 0){   //S12
        Delay100ms();
        if(P33 == 0){
            key_value = 5;
            while(P33 == 0);
        }
    }
    if(P32 == 0){   //S13
        Delay100ms();
        if(P32 == 0){
            key_value = 6;
            while(P32 == 0);
        }
    }
}

void Key_login(){
    switch(key_value){
        case 1: //S4
            if(Free_flag){
                if(coordinate_flag){
                    Run_flag = 1;
                    Free_flag = 0;
                }
            }
            if(Run_flag){
                Wait_flag = 1;
                Run_flag = 0;
            }
            if(Wait_flag){
                if(Obstacle_flag){
                    Run_flag = 1;
                    Wait_flag = 0;
                }
            }
            break;
        case 2: //S5
            if(Free_flag){
                Position_value[0] = 0;
                Position_value[1] = 0;
            }
            break;
        case 3: //S8
            S8_cnt = (S8_cnt + 1) % 3;
            break;
        case 4: //S9
            if(S8_cnt == 2){
                S9_cnt = (S9_cnt + 1) % 2;
            }
            break;
        case 5: //S12
            if(S8_cnt == 2){
                if(S9_cnt == 0){
                    if(R_Parameter < 20){
                        R_Parameter += 1;
                    }
                }
                if(S9_cnt == 1){
                    if(B_Parameter < 90){
                        R_Parameter += 5;
                    }
                }
            }
            break;
        case 6: //S13
             if(S8_cnt == 2){
                if(S9_cnt == 0){
                    if(R_Parameter > 10){
                        R_Parameter -= 1;
                    }
                }
                if(S9_cnt == 1){
                    if(B_Parameter > -90){
                        R_Parameter -= 5;
                    }
                }
            } 
            break;  
    }
}