#include <stc15f2k60s2.h>
#include "Delay.h"

sbit S4 = P3^3;
sbit S5 = P3^2;

unsigned char S4_Password = 1;          // 1=模式界面(MODE)，0=DAC界面
unsigned char cur_mode = 1;   // 默认模式一（温度）

// 按键扫描（
unsigned char Key_Scan(){
    unsigned char key = 0;
    if(S4 == 0){
        Delay10ms();
        while(S4 == 0);  // 等待按键释放
        key = 1;
    }
    if(S5 == 0){
        Delay10ms();
        while(S5 == 0);  // 等待按键释放
        key = 2;
    }
    return key;
}

// 按键业务逻辑
unsigned char Key_Work(){
    unsigned char num = Key_Scan();
    
    // S4：仅在模式界面(MODE)切换模式一/二
    if(num == 1 && S4_Password == 1){
        cur_mode = (cur_mode == 1) ? 2 : 1;
    }
    
    // S5：切换界面（MODE ? DAC）
    if(num == 2){
        S4_Password = !S4_Password;
    }
    
    // 返回当前状态标识：高字节=界面(1=MODE,0=DAC)，低字节=模式(1/2)
    return (S4_Password << 4) | cur_mode;
}