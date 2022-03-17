/**********************************************************
    不建议更改此文档，相关函数功能请查看相关头文件定义
**********************************************************/
#include "PIT.h"

void PIT_init_ms(int n,int time)
{
	if(n==0)
	{	
		AUXR &= 0x7f;  // T0, 12T 模式
		TMOD |= 0x00;  //定时器0工作方式0
		TH0 = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    TL0 = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		ET0 = 1;
    TR0 = 1;
	}
	if(n==1)	
	{		
		AUXR &= 0xbf;  // T1, 12T 模式
		TMOD |= 0x00;  //定时器1工作方式0
		TH1 = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    TL1 = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		ET1 = 1;
    TR1 = 1;
	}
	if(n==2)	
	{		
		AUXR &= 0xfb;  // T2, 12T 模式
		T2H = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    T2L = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		IE2 |= ET2;                                  //使能定时器中断
    AUXR |= 0x10;                                //启动定时器2
	}
	if(n==3)	
	{		
		T4T3M &= 0xf8;  // T3, 12T 模式
		T3H = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    T3L = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		IE2 |= ET3;                                  //使能定时器3中断
    T4T3M |= 0x08;                               //启动定时器3
	}
	if(n==4)	
	{		
		T4T3M &= 0x8f;  // T4, 12T 模式
		T4H = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    T4L = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		IE2 |= ET4;                                  //使能定时器4中断
    T4T3M |= 0x80;                               //启动定时器4
	}
	EA=1;            //允许所有中断
}  

void PIT_init_us(int n,int time)
{
	if(n==0)
	{	
		AUXR |= 0x80;  // T0, 1T 模式
		TMOD |= 0x00;  //定时器0工作方式1
		TH0 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    TL0 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		ET0 = 1;
    TR0 = 1;
	}
	if(n==1)	
	{
		AUXR |= 0x40;  // T1, 1T 模式
		TMOD |= 0x00;  //定时器1工作方式1
		TH1 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    TL1 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		ET1 = 1;
    TR1 = 1;
	}
	if(n==2)	
	{		
		AUXR |= 0x04;  // T2, 1T 模式
		T2H = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    T2L = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		IE2 |= ET2;                                  //使能定时器中断
    AUXR |= 0x10;                                //启动定时器2
	}
	if(n==3)	
	{	
		T4T3M &= 0xf8;  // T3, 1T 模式		
		T4T3M |= 0x02;  // T3, 1T 模式
		T3H = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    T3L = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		IE2 |= ET3;                                  //使能定时器3中断
    T4T3M |= 0x08;                               //启动定时器3
	}
	if(n==4)	
	{		
		T4T3M &= 0x8f;  // T4, 1T 模式
		T4T3M |= 0x20;  // T4, 1T 模式
		T4H = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    T4L = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		IE2 |= ET4;                                  //使能定时器4中断
    T4T3M |= 0x80;                               //启动定时器4
	}
	EA=1;            //允许所有中断
}