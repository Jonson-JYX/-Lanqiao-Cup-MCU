#include <stc15f2k60s2.h>
#include "KEY.h"
#include "Common.h"
#include "UItrasound.h"
#include "LED_Display.h"

void LED_login(){
	if(dat1 > value){
		LED(0xFE);
	}
	else{
		LED(0xFF);
	}
}