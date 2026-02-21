#include <stc15f2k60s2.h>
#include "Delay.h"

int S4_cnt = 1;
bit S8_password = 0;

//°´¼üÉ¨Ãèº¯Êý
unsigned char Key_Scan(){
	unsigned char key = 0;
	P30 = 1,P31 = 1,P32 = 1,P33 = 0;
	if(P44 == 0){
		Delay100ms();
		while(P44 == 0){
			key = 1;
		}
	}
	if(P42 == 0){
		Delay100ms();
		while(P42 == 0){
			key = 2;
		}
	}
	return key;
}

//°´¼üÂß¼­º¯Êý
void Key_logic(){
	unsigned char key = Key_Scan();
	if(key == 1){
		S4_cnt++;
	}
	if(key == 2){
		S8_password = 1;
	}
}
