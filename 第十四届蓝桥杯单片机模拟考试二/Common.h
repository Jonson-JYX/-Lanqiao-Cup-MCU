#ifndef Common_H
#define Common_H
#define LED(X) {P0 = X;P2 = (P2 & 0x1F) | 0x80;P2 &= 0x1F;}
#define SEG(X) {P0 = X;P2 = (P2 & 0x1F) | 0xE0;P2 &= 0x1F;}
#define COM(X) {P0 = X;P2 = (P2 & 0x1F) | 0xC0;P2 &= 0x1F;}
#define BUZ(X) {P2 = (P2 & 0x1F) | 0xA0;if(X == 0xBF) P0 |= (1<<6);else P0 &= ~(1<<6);P2 &= 0x1F;}
#define REY(X) {P2 = (P2 & 0x1F) | 0xA0;if(X == 0xEF) P0 |= (1<<4);else P0 &= ~(1<<4);P2 &= 0x1F;}
#endif // !Common_H
