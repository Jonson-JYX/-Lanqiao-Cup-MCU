#ifndef Common_H
#define Common_H
#define LED(x) {P0 = x;P2 = (P2 & 0x1F) | 0x80;P2 &= 0x1F;}
#define SEG(x) {P0 = x;P2 = (P2 & 0x1F) | 0xE0;P2 &= 0x1F;}
#define COM(x) {P0 = x;P2 = (P2 & 0x1F) | 0xC0;P2 &= 0x1F;}
#define BUZ(x) {P0 = x;P2 = (P2 & 0x1F) | 0xA0;P2 &= 0x1F;}
#define REY(x) {P0 = x;P2 = (P2 & 0x1F) | 0xA0;P2 &= 0x1F;}
#endif // !Common_H