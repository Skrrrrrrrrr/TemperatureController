#include "config.h"


extern void PIT_init_ms(int n,int time); //PIT模块ms初始化函数，默认使用定时器工作方式1，12T工作方式
/*
取值：n:要使用的定时器模块     例：0 为 定时器0
																	 1 为 定时器1
																	 2 为 定时器2
																	 3 为 定时器3
																	 4 为 定时器4
取值：time:要定时中断的时长    取值范围:  1-32ms(24MHZ)
*/

extern void PIT_init_us(int n,int time); //PIT模块us初始化函数，默认使用定时器工作方式1，1T工作方式
/*
取值：n:要使用的定时器模块     例：0 为 定时器0
																	 1 为 定时器1
																	 2 为 定时器2
																	 3 为 定时器3
																	 4 为 定时器4
取值：time:要定时中断的时长    取值范围:  1-2730us(24MHZ)
*/