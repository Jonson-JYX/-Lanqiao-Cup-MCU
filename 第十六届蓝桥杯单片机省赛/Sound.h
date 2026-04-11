#ifndef Sound_H
#define Sound_H
extern unsigned char sound_value;    //声音强度值
extern unsigned char sound_dat;     //声音参数
extern unsigned char sound_status;   //声音状态值
extern unsigned char sound_storage1; //声音存储值1
extern unsigned char sound_storage2; //声音存储值2
extern bit sound_flag;              //声音标志位
void Sound_login();
#endif // !Sound_H