#include "PCA.h"

unsigned char PCA_MODE = 0; //PCA模式变量
unsigned int PCA0_n = 0;
unsigned int PCA1_n = 0;
unsigned int PCA2_n = 0;
unsigned int PCA3_n = 0;

int PCA0_count = 0;
int PCA1_count = 0;
int PCA2_count = 0;
int PCA3_count = 0;

unsigned int PCA0_HZ;
unsigned int PCA1_HZ;
unsigned int PCA2_HZ;
unsigned int PCA3_HZ;

unsigned char PCA0_IO;
unsigned char PCA1_IO;
unsigned char PCA2_IO;
unsigned char PCA3_IO;

unsigned int PCA0_FallTime;
unsigned int PCA1_FallTime;
unsigned int PCA2_FallTime;
unsigned int PCA3_FallTime;
//PCA脉冲计数初始化函数
void PCA_Count_init(int pin, char dirIO)
{
	PCA_MODE = 3; //PCA模式设置为脉冲计数模式
	if (pin / 10 % 10 == 1)
	{
		P_SW1 |= 0x00; //PCA使用P14-P17口
		P1M0 &= ~0xF0; //P14-P17口高阻态
		P1M1 |= 0xF0;
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCA使用P23-P26口
		P2M0 &= ~0x78; //P23-P26口高阻态
		P2M1 |= 0x78;
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCA使用P30-P33口
		P3M0 &= ~0x0F; //P30-P33口高阻态
		P3M1 |= 0x0F;
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCA使用P70-P73口
		P7M0 &= ~0x0F; //P70-P73口高阻态
		P7M1 |= 0x0F;
	}
	CCON = 0x00;
	CMOD = 0x08; //PCA时钟为系统时钟
	CL = 0x00;
	CH = 0x00;
	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{
		PCA0_IO = dirIO;
		PCA0_count = 0;
		CCAPM0 = 0x11;
		CCAP0L = 0;
		CCAP0H = 0; //扩展外部端口CCP0为下降沿中断口
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{
		PCA1_IO = dirIO;
		PCA1_count = 0;
		CCAPM1 = 0x11;
		CCAP1L = 0;
		CCAP1H = 0; //扩展外部端口CCP1为下降沿中断口
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{
		PCA2_IO = dirIO;
		PCA2_count = 0;
		CCAPM2 = 0x11;
		CCAP2L = 0;
		CCAP2H = 0; //扩展外部端口CCP2为下降沿中断口
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{
		PCA3_IO = dirIO;
		PCA3_count = 0;
		CCAPM3 = 0x11;
		CCAP3L = 0;
		CCAP3H = 0; //扩展外部端口CCP3为下降沿中断口
	}
	CR = 1; //启动PCA时钟
	EA = 1; //允许所有中断
}

int PCA_Count_get(int n) //获取某通道脉冲计数值
{
	int m;
	switch (n)
	{
	case 0:
		m = PCA0_count;
		PCA0_count = 0;
		break;
	case 1:
		m = PCA1_count;
		PCA1_count = 0;
		break;
	case 2:
		m = PCA2_count;
		PCA2_count = 0;
		break;
	case 3:
		m = PCA3_count;
		PCA3_count = 0;
		break;
	default:
		break; //其他情况
	}
	return m;
}

//PCA-PWM模式初始化函数
void PCA_Pwm_init(int pin, int freq, int pwm)
{
	PCA_MODE = 1;			//PCA模式设置为PWM模式
	if (pin / 10 % 10 == 1) //PCA端口切换
	{
		P_SW1 |= 0x00; //PCA使用P14-P17口
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCA使用P23-P26口
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCA使用P30-P33口
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCA使用P70-P73口
	}

	AUXR &= 0x7f; // T0, 12T 模式 作为PCA时钟
	TMOD |= 0x02; //定时器0工作方式2   8位自动重转模式
	TH0 = 256 - (int)((Main_Fosc / 12 / 256) / (freq * 4));
	TL0 = TH0;
	TR0 = 1; //定时器开始工作

	CCON = 0x00;
	CMOD = 0x04; //PCA时钟为定时器0溢出脉冲
	CL = 0x00;
	CH = 0x00;

	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{													  //扩展外部端口CCP0
		CCAPM0 = 0x42;									  //PCA模块0为PWM工作模式
		PCA_PWM0 = 0xc0;								  //PCA模块0输出10位PWM
		PCA0_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM0 += PCA0_n / 256 * 4 + PCA0_n / 256 * 16; //PWM占空比设置 高两位
		CCAP0H = CCAP0L = PCA0_n % 256;					  //PWM占空比设置 低八位
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{													  //扩展外部端口CCP1
		CCAPM1 = 0x42;									  //PCA模块1为PWM工作模式
		PCA_PWM1 = 0xc0;								  //PCA模块1输出10位PWM
		PCA1_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM1 += PCA1_n / 256 * 4 + PCA1_n / 256 * 16; //PWM占空比设置 高两位
		CCAP1H = CCAP1L = PCA1_n % 256;					  //PWM占空比设置 低八位
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{													  //扩展外部端口CCP2
		CCAPM2 = 0x42;									  //PCA模块2为PWM工作模式
		PCA_PWM2 = 0xc0;								  //PCA模块2输出10位PWM
		PCA2_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM2 += PCA2_n / 256 * 4 + PCA2_n / 256 * 16; //PWM占空比设置 高两位
		CCAP2H = CCAP2L = PCA2_n % 256;					  //PWM占空比设置 低八位
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{													  //扩展外部端口CCP3
		CCAPM3 = 0x42;									  //PCA模块3为PWM工作模式
		PCA_PWM3 = 0xc0;								  //PCA模块3输出10位PWM
		PCA3_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM3 += PCA3_n / 256 * 4 + PCA3_n / 256 * 16; //PWM占空比设置 高两位
		CCAP3H = CCAP3L = PCA3_n % 256;					  //PWM占空比设置 低八位
	}
	CR = 1; //启动PCA时钟
}

void PCA_Pwm_change(int pin, int pwm) //改变PWM占空
{
	switch (pin)
	{
	case 0:
	{
		PCA_PWM0 = 0xc0;								  //PCA模块0输出10位PWM
		PCA0_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM0 += PCA0_n / 256 * 4 + PCA0_n / 256 * 16; //PWM占空比设置 高两位
		CCAP0H = CCAP0L = PCA0_n % 256;					  //PWM占空比设置 低八位
		break;
	}
	case 1:
	{
		PCA_PWM1 = 0xc0;								  //PCA模块1输出10位PWM
		PCA1_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM1 += PCA1_n / 256 * 4 + PCA1_n / 256 * 16; //PWM占空比设置 高两位
		CCAP1H = CCAP1L = PCA1_n % 256;					  //PWM占空比设置 低八位
		break;
	}
	case 2:
	{
		PCA_PWM2 = 0xc0;								  //PCA模块2输出10位PWM
		PCA2_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM2 += PCA2_n / 256 * 4 + PCA2_n / 256 * 16; //PWM占空比设置 高两位
		CCAP2H = CCAP2L = PCA2_n % 256;					  //PWM占空比设置 低八位
		break;
	}
	case 3:
	{
		PCA_PWM3 = 0xc0;								  //PCA模块3输出10位PWM
		PCA3_n = (int)(((10000 - pwm) / 10000.0) * 1024); //计算PWM占空初值
		PCA_PWM3 += PCA3_n / 256 * 4 + PCA3_n / 256 * 16; //PWM占空比设置 高两位
		CCAP3H = CCAP3L = PCA3_n % 256;					  //PWM占空比设置 低八位
		break;
	}
	default:
		break; //其他情况
	}
}

//PCA高速脉冲模式初始化函数
void PCA_Pulse_init(int pin, unsigned long freq)
{
	PCA_MODE = 2; //PCA模式设置为脉冲计数模式
	if (pin / 10 % 10 == 1)
	{
		P_SW1 |= 0x00; //PCA使用P14-P17口
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCA使用P23-P26口
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCA使用P30-P33口
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCA使用P70-P73口
	}
	CCON = 0x00;
	CMOD = 0x08; //PCA时钟为系统时钟
	CL = 0x00;
	CH = 0x00;
	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{
		CCAPM0 = 0x4d; //PCA模块0为16位定时器模式并使能脉冲输出
		PCA0_HZ = Main_Fosc / 2 / freq;
		PCA0_n = PCA0_HZ;
		CCAP0L = PCA0_n;
		CCAP0H = PCA0_n >> 8;
		PCA0_n += PCA0_HZ;
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{
		CCAPM1 = 0x4d; //PCA模块0为16位定时器模式并使能脉冲输出
		PCA1_HZ = Main_Fosc / 2 / freq;
		PCA1_n = PCA1_HZ;
		CCAP1L = PCA1_n;
		CCAP1H = PCA1_n >> 8;
		PCA1_n += PCA1_HZ;
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{
		CCAPM2 = 0x4d; //PCA模块0为16位定时器模式并使能脉冲输出
		PCA2_HZ = Main_Fosc / 2 / freq;
		PCA2_n = PCA2_HZ;
		CCAP2L = PCA2_n;
		CCAP2H = PCA2_n >> 8;
		PCA2_n += PCA2_HZ;
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{
		CCAPM3 = 0x4d; //PCA模块0为16位定时器模式并使能脉冲输出
		PCA3_HZ = Main_Fosc / 2 / freq;
		PCA3_n = PCA3_HZ;
		CCAP3L = PCA3_n;
		CCAP3H = PCA3_n >> 8;
		PCA3_n += PCA3_HZ;
	}
	CR = 1; //启动PCA时钟
	EA = 1; //允许所有中断
}

//PCA脉冲宽度测量初始化函数
void PCA_Width_init(int pin)
{
	PCA_MODE = 4; //PCA模式设置为脉冲计数模式
	if (pin / 10 % 10 == 1)
	{
		P_SW1 |= 0x00; //PCA使用P14-P17口
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCA使用P23-P26口
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCA使用P30-P33口
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCA使用P70-P73口
	}
	CCON = 0x00;
	CMOD = 0x00; //PCA时钟为系统时钟/12 = 2MHZ，一个脉冲0.5us
	CL = 0x00;
	CH = 0x00;
	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{
		PCA0_IO = pin;
		PCA0_n = 0;		 //计数值清0
		CCAPM0 = 0x31;	 //PCA模块上升沿下降沿都中断，允许捕获中断
		PCA_PWM0 = 0x00; //8位PWM宽度（没用）
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{
		PCA1_IO = pin;
		PCA1_n = 0;		 //计数值清0
		CCAPM1 = 0x31;	 //PCA模块上升沿下降沿都中断，允许捕获中断
		PCA_PWM1 = 0x00; //8位PWM宽度（没用）
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{
		PCA2_IO = pin;
		PCA2_n = 0;		 //计数值清0
		CCAPM2 = 0x31;	 //PCA模块上升沿下降沿都中断，允许捕获中断
		PCA_PWM2 = 0x00; //8位PWM宽度（没用）
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{
		PCA3_IO = pin;
		PCA3_n = 0;		 //计数值清0
		CCAPM3 = 0x31;	 //PCA模块上升沿下降沿都中断，允许捕获中断
		PCA_PWM3 = 0x00; //8位PWM宽度（没用）
	}
	CR = 1; //启动PCA时钟
	EA = 1; //允许所有中断
}

uint PCA_Width_get(int pin) //获取某通道脉冲宽度
{
	int m;
	switch (pin)
	{
	case 0:
		m = PCA0_FallTime;
		break;
	case 1:
		m = PCA1_FallTime;
		break;
	case 2:
		m = PCA2_FallTime;
		break;
	case 3:
		m = PCA3_FallTime;
		break;
	default:
		break; //其他情况
	}
	return m;
}