#include <stc15f2k60s2.h>
#include "Delay.h"

sbit S4 = P3^3;

unsigned char disp_mode = 1;

unsigned char Key_Scan(){
	if(S4 == 0){
		Delay500us(); // 短消抖（替代原500ms长延时，避免切换卡顿）
		if(S4 == 0){
			// 松手检测
			while(S4 == 0);
			// 模式切换：1→2→3→1循环
			disp_mode++;
			if(disp_mode > 3){
				disp_mode = 1;
			}
			return disp_mode;
		}
	}
	return disp_mode; // 返回当前模式（无按键时保持原模式）
}