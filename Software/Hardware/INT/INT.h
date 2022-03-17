#ifndef __INT_H
#define __INT_H

#include "config.h"

extern void INT_init(int n, int mode); //外部中断模块初始化函数
/*
取值：n:要使用的外部中断模块，取值范围0-4     例：0 为 外部中断0
																									1 为 外部中断1
																									2 为 外部中断2
																									3 为 外部中断3
																									4 为 外部中断4
																		 
取值：mode:要使用中断触发方式     例：0 为 下降沿触发
																	    1 为 上升沿和下降沿都触发（仅外部中断0和1具有次功能）
*/

#endif