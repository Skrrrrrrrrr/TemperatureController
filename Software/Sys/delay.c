#include "delay.h"

void exact_delay(u8 a, u8 b, u8 c) //延时函数
{
	do
	{
		do
		{
			while (--c)
				;
		} while (--b);
	} while (--a);
}

void delay_X_ms(u16 x) //延时Xms 取值范围1-1000
{
	u8 A, B, C;
	u32 T;
	T = x * 3600.0 * Main_Fosc_KHZ / 11059.2;

	A = (T / 65536) % 256 + 1;
	B = (T / 256) % 256 + 1;
	C = T % 256;

	exact_delay(A, B, C); //延时Xus 取值范围1-1000
}

void delay_X_us(u16 x)
{
	// x = x * Main_Fosc_KHZ / 11059.2;
	while (x--)
		;
}
