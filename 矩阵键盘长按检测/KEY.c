#include <stc15f2k60s2.h>
#include "Timer.h"

unsigned char Key_value = 0;
unsigned char Key_Down = 0;
unsigned char Key_Long = 0;

unsigned char status = 0;
unsigned int press_cnt = 0;
unsigned char current_key = 0;

// 矩阵键盘扫描，返回按键码(1-16)或0
unsigned char KEY_Read(void)
{
	// 扫描第一行 (P44)
	P44 = 0; P42 = 1; P35 = 1; P34 = 1;
	if(P33 == 0) return 1;
	if(P32 == 0) return 2;
	if(P31 == 0) return 3;
	if(P30 == 0) return 4;
	
	// 扫描第二行 (P42)
	P44 = 1; P42 = 0; P35 = 1; P34 = 1;
	if(P33 == 0) return 5;
	if(P32 == 0) return 6;
	if(P31 == 0) return 7;
	if(P30 == 0) return 8;
	
	// 扫描第三行 (P35)
	P44 = 1; P42 = 1; P35 = 0; P34 = 1;
	if(P33 == 0) return 9;
	if(P32 == 0) return 10;
	if(P31 == 0) return 11;
	if(P30 == 0) return 12;
	
	// 扫描第四行 (P34)
	P44 = 1; P42 = 1; P35 = 1; P34 = 0;
	if(P33 == 0) return 13;
	if(P32 == 0) return 14;
	if(P31 == 0) return 15;
	if(P30 == 0) return 16;
	
	return 0;
}

void KEY_Scan(void)
{
	unsigned char key_num;
	
	key_num = KEY_Read();
	
	switch(status)
	{
		case 0:  // 空闲状态
			if(key_num != 0)
			{
				current_key = key_num;
				press_cnt = 0;
				status = 1;
			}
			break;
			
		case 1:  // 消抖状态
			if(key_num == current_key)
			{
				press_cnt++;
				if(press_cnt >= 2)  // 20ms消抖
				{
					status = 2;
				}
			}
			else
			{
				status = 0;
			}
			break;
			
		case 2:  // 等待释放或长按
			if(key_num == current_key)
			{
				press_cnt++;
				if(press_cnt >= 100)  // 1000ms长按
				{
					// 长按返回 16 + current_key (17-32)
					Key_Long = 1;
					Key_value = 16 + current_key;
					status = 3;
				}
			}
			else  // 短按释放
			{
				// 短按返回 current_key (1-16)
				Key_Down = 1;
				Key_value = current_key;
				status = 0;
			}
			break;
			
		case 3:  // 长按等待释放
			if(key_num != current_key)
			{
				status = 0;
			}
			break;
	}
}

void KEY_Init(void)
{
	status = 0;
	press_cnt = 0;
	current_key = 0;
	Key_value = 0;
	Key_Down = 0;
	Key_Long = 0;
}