#include <stc15f2k60s2.h>
#include "Delay.h"
#include "Common.h"
#include "LED.h"
#include "LED_Display.h"

sbit S4 = P3^3;
sbit S5 = P3^2;
sbit S6 = P3^1;
sbit S7 = P3^0;

bit password = 0;
bit s6_trigger = 0;     // S6触发标志：1=需要同步亮灯/显示
unsigned int s6_timer = 0; // 计时变量（ms），到2000ms后关闭
unsigned char num = 0;


//按键扫描函数
unsigned char Key_Scan(){
	if(S4 == 0){
		Delay500us(); 
		if(S4 == 0){
			while(S4 == 0); 
			return 1;
		}
	}
	if(S5 == 0){
		Delay500us(); 
		if(S5 == 0){
			while(S5 == 0); 
			return 2;
		}
	}
	if(S6 == 0){
		Delay500us(); 
		if(S6 == 0){
			while(S6 == 0); 
			return 3;
		}
	}
	if(S7 == 0){
		Delay500us(); 
		if(S7 == 0){
			while(S7 == 0); 
			return 4;
		}
	}
	return 0;
}

//返回计数器的数字
unsigned char Number(){
	unsigned char key = Key_Scan();
    
    // S7：锁定/解锁逻辑
    if(key == 4){
        password = !password;          // 切换锁定状态
        if(password){
            LED(0x7F);  // L8点亮（P0.7=0，0x7F=0111 1111）
        }else{
            LED(0xFF);  // L8熄灭（所有LED灭）
        }
        return num;
    }
    
    // 锁定状态下，S4-S6失效
    if(password){
        return num;
    }
    
    // 解锁状态下，处理S4-S6
    switch (key){
        case 1:  // S4：加1
			if(num < 100) {
				num++;
			}
            break;
        case 2:  // S5：减1（防止负数）
            if(num > 0){
                num--;
            }
            break;
        case 3:  // S6：清零 + L1亮2s
            num = 0;
			s6_trigger = 1;    // 标记需要同步显示/亮灯
            s6_timer = 0;      // 计时清零
            break;
    }
    return num;
}

void Timer0_Init(void)
{
    TMOD &= 0xF0;  // 清空Timer0模式
    TMOD |= 0x01;  // 设置为16位自动重装模式
    TL0 = 0x66;    // 初值低8位
    TH0 = 0xFC;    // 初值高8位
    TF0 = 0;       // 清除溢出标志
    TR0 = 1;       // 启动Timer0
    ET0 = 1;       // 使能Timer0中断
    EA = 1;        // 开启总中断
}

// Timer0中断服务函数（1ms执行一次）
void Timer0_ISR(void) interrupt 1
{
    TL0 = 0x66;    // 重新加载初值（避免计时偏差）
    TH0 = 0xFC;
    
    // 处理S6触发的同步显示/亮灯
    if(s6_trigger == 1)
    {
        s6_timer++;          // 计时+1ms
        LED_Display_Show();  // 持续刷新数码管显示0
        LED(0xFE);           // 持续点亮L1（0xFE=11111110）
        
        // 计时达到2000ms（2秒），关闭同步
        if(s6_timer >= 300)
        {
            s6_trigger = 0;  // 清除触发标志
            s6_timer = 0;    // 计时清零
            LED(0xFF);       // 关闭LED灯
        }
    }
    else
    {
        // 非S6触发时，正常刷新数码管（显示当前num）
        LED_Display_Show();
    }
}