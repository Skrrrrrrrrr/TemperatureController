#ifndef __DELAY_H
#define __DELAY_H

#include "config.h"

extern void delay_X_ms(u16 x);
extern void delay_X_us(u16 x);
extern void exact_delay(u8 a, u8 b, u8 c);

#endif