/**********************************************************
    ��������Ĵ��ĵ�����غ���������鿴���ͷ�ļ�����
**********************************************************/
#include "PIT.h"

void PIT_init_ms(int n,int time)
{
	if(n==0)
	{	
		AUXR &= 0x7f;  // T0, 12T ģʽ
		TMOD |= 0x00;  //��ʱ��0������ʽ0
		TH0 = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    TL0 = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		ET0 = 1;
    TR0 = 1;
	}
	if(n==1)	
	{		
		AUXR &= 0xbf;  // T1, 12T ģʽ
		TMOD |= 0x00;  //��ʱ��1������ʽ0
		TH1 = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    TL1 = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		ET1 = 1;
    TR1 = 1;
	}
	if(n==2)	
	{		
		AUXR &= 0xfb;  // T2, 12T ģʽ
		T2H = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    T2L = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		IE2 |= ET2;                                  //ʹ�ܶ�ʱ���ж�
    AUXR |= 0x10;                                //������ʱ��2
	}
	if(n==3)	
	{		
		T4T3M &= 0xf8;  // T3, 12T ģʽ
		T3H = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    T3L = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		IE2 |= ET3;                                  //ʹ�ܶ�ʱ��3�ж�
    T4T3M |= 0x08;                               //������ʱ��3
	}
	if(n==4)	
	{		
		T4T3M &= 0x8f;  // T4, 12T ģʽ
		T4H = (65535-(int)(time*(Main_Fosc_KHZ/12)))/256;
    T4L = (65535-(int)(time*(Main_Fosc_KHZ/12)))%256;
		IE2 |= ET4;                                  //ʹ�ܶ�ʱ��4�ж�
    T4T3M |= 0x80;                               //������ʱ��4
	}
	EA=1;            //���������ж�
}  

void PIT_init_us(int n,int time)
{
	if(n==0)
	{	
		AUXR |= 0x80;  // T0, 1T ģʽ
		TMOD |= 0x00;  //��ʱ��0������ʽ1
		TH0 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    TL0 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		ET0 = 1;
    TR0 = 1;
	}
	if(n==1)	
	{
		AUXR |= 0x40;  // T1, 1T ģʽ
		TMOD |= 0x00;  //��ʱ��1������ʽ1
		TH1 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    TL1 = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		ET1 = 1;
    TR1 = 1;
	}
	if(n==2)	
	{		
		AUXR |= 0x04;  // T2, 1T ģʽ
		T2H = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    T2L = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		IE2 |= ET2;                                  //ʹ�ܶ�ʱ���ж�
    AUXR |= 0x10;                                //������ʱ��2
	}
	if(n==3)	
	{	
		T4T3M &= 0xf8;  // T3, 1T ģʽ		
		T4T3M |= 0x02;  // T3, 1T ģʽ
		T3H = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    T3L = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		IE2 |= ET3;                                  //ʹ�ܶ�ʱ��3�ж�
    T4T3M |= 0x08;                               //������ʱ��3
	}
	if(n==4)	
	{		
		T4T3M &= 0x8f;  // T4, 1T ģʽ
		T4T3M |= 0x20;  // T4, 1T ģʽ
		T4H = (65535-(int)(time*(Main_Fosc_KHZ/1000)))/256;
    T4L = (65535-(int)(time*(Main_Fosc_KHZ/1000)))%256;
		IE2 |= ET4;                                  //ʹ�ܶ�ʱ��4�ж�
    T4T3M |= 0x80;                               //������ʱ��4
	}
	EA=1;            //���������ж�
}