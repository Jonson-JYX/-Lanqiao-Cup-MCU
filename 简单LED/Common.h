#ifndef Common_H
#define Common_H
#define LED(X) {P0 = X;P2 = (P2 & 0x1F) | 0x80;P2 &= 0x1F;}
#define SEG(X) {P0 = X;P2 = (P2 & 0x1F) | 0xE0;P2 &= 0x1F;}
#define COM(X) {P0 = X;P2 = (P2 & 0x1F) | 0xC0;P2 &= 0x1F;}
#define BUZ(X) {P0 = X;P2 = (P2 & 0x1F) | 0xA0;P2 &= 0x1F;}
#endif // !Common_H