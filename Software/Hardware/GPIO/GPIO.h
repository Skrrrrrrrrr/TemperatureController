#ifndef __GPIO_H
#define __GPIO_H

#include "config.h"

extern u8 psw2_st;

void IO_init();

extern void GPIO_init_pin(int pin, int mode); //初始化单个IO引脚函数
/*
取值：pin:要初始化的引脚   例：11 为 P1^1
取值：mode:要初始化模式    例：0 为 准双向   5mA小电流工作，选择
															 1 为 强推挽   20mA大电流输出，选择
															 2 为 高阻态   禁止电流流入流出，A/D转换选择
															 3 为 开漏     取消内部弱上拉电阻，选择
*/
extern bit Get_IO(int IO); //读取单个IO状态

extern void Out_IO(unsigned char IO, bit status); //单个IO输出

#endif