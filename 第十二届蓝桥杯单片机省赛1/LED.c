#include <STC15F2K60S2.H>
#include "KEY.h"
#include "Common.h"

code unsigned char LED_Table[] = {
    0xFC,   //模式一温度显示界面
    0xFA,   //模式一参数设置界面
    0xF6,   //模式一DAC输出界面
    0xFD,   //模式二温度显示界面
    0xFB,   //模式二参数设置界面
    0xF7    //模式二DAC输出界面
};

//LED逻辑函数
void LED_Login(){
    if(S5_cnt %2 == 0 && S4_cnt % 3 == 0){
        LED(LED_Table[0]);
    }
    if(S5_cnt %2 == 0 && S4_cnt % 3 == 1){
        LED(LED_Table[1]);
    }
    if(S5_cnt %2 == 0 && S4_cnt % 3 == 2){
        LED(LED_Table[2]);
    }
    if(S5_cnt %2 == 1 && S4_cnt % 3 == 0){
        LED(LED_Table[3]);
    }
    if(S5_cnt %2 == 1 && S4_cnt % 3 == 1){
        LED(LED_Table[4]);
    }
    if(S5_cnt %2 == 1 && S4_cnt % 3 == 2){
        LED(LED_Table[5]);
    }
}