#ifndef __TIMER_H
#define __TIMER_H

#include "config.h"
// #define Timer_xUs_yT(x, y) (u32)(1000 / x / y) //周期为x us，工作模式为y T的定时器
#define Timer_xUs_yT(x, y) (u32)(5 * 1e5 / x * y) //周期为x us，工作模式为y T的定时器

extern u16 timer4Cnt;

void Timer0_init(bool irtEn, u32 initValue, u8 TMode, bool T0_1T, bool clkoutEn);
void Timer1_init(bool irtEn, u32 initValue, u8 TMode, bool T1_1T, bool clkoutEn);
void Timer2_init(bool irtEn, u32 initValue, u8 TMode, bool T1_1T, bool clkoutEn);
void Timer3_init(bool irtEn, u32 initValue, bool T3_1T, bool clkoutEn);
void Timer4_init(bool irtEn, u32 initValue, bool T4_1T, bool clkoutEn);

void Timer3_start(void);
void Timer3_stop(void);
void Timer4_start(void);
void Timer4_stop(void);

#endif