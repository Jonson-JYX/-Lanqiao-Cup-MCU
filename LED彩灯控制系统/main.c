#include <stc15f2k60s2.h>
#include "LED.h"
#include "DISPALY.h"
#include "KEY.h"
#include "DELAY.h"
#include "COMMON.h"

//定义位选
bit Key_Code = 0;

//初始化函数
void Init_MCU(){
	LED(0xFF);
	COM(0xFF);
	SEG(0xFF);
	BUZ(0x00);
}

void main(void){
	//获取按键值
	unsigned char Key1 = 0,Key2 = 0;
	//模式控制值
	unsigned char mol = 0;
	Init_MCU();
	while(1){
		Key1 = Key_Scan();
		Key2 = Key_Scan();
		switch(Key1){
			case 1:
				Key_Code = 1;
				break;
			case 2:
				Key_Code = 0;
				break;
		}
		if(Key_Code){
			switch(Key2){
				case 3:
					mol++;
					if(mol > 4){
						mol = 1;
					}
					SEG_Display(0);
					break;
				case 4:
					mol--;
					if(mol < 1){
						mol = 4;
					}
					SEG_Display(0);
					break;
			}
			LED_Show(mol);
			SEG_Display(0);
		}
		SEG_Display(1);
	}
}