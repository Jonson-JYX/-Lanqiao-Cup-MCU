#ifndef __KEY_H__
#define __KEY_H__

extern unsigned char Key_value;
extern unsigned char Key_Down;
extern unsigned char Key_Long;

void KEY_Init(void);
void KEY_Scan(void);

#endif