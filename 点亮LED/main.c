#include <stc15f2k60s2.h>
#include "led.h"

void main(void){
	LED(0xFF);
	while(1){
		LED(0x0F);
	}
}