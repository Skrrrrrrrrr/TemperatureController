#include "PCA.h"

unsigned char PCA_MODE = 0; //PCAģʽ����
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
//PCA���������ʼ������
void PCA_Count_init(int pin, char dirIO)
{
	PCA_MODE = 3; //PCAģʽ����Ϊ�������ģʽ
	if (pin / 10 % 10 == 1)
	{
		P_SW1 |= 0x00; //PCAʹ��P14-P17��
		P1M0 &= ~0xF0; //P14-P17�ڸ���̬
		P1M1 |= 0xF0;
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCAʹ��P23-P26��
		P2M0 &= ~0x78; //P23-P26�ڸ���̬
		P2M1 |= 0x78;
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCAʹ��P30-P33��
		P3M0 &= ~0x0F; //P30-P33�ڸ���̬
		P3M1 |= 0x0F;
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCAʹ��P70-P73��
		P7M0 &= ~0x0F; //P70-P73�ڸ���̬
		P7M1 |= 0x0F;
	}
	CCON = 0x00;
	CMOD = 0x08; //PCAʱ��Ϊϵͳʱ��
	CL = 0x00;
	CH = 0x00;
	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{
		PCA0_IO = dirIO;
		PCA0_count = 0;
		CCAPM0 = 0x11;
		CCAP0L = 0;
		CCAP0H = 0; //��չ�ⲿ�˿�CCP0Ϊ�½����жϿ�
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{
		PCA1_IO = dirIO;
		PCA1_count = 0;
		CCAPM1 = 0x11;
		CCAP1L = 0;
		CCAP1H = 0; //��չ�ⲿ�˿�CCP1Ϊ�½����жϿ�
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{
		PCA2_IO = dirIO;
		PCA2_count = 0;
		CCAPM2 = 0x11;
		CCAP2L = 0;
		CCAP2H = 0; //��չ�ⲿ�˿�CCP2Ϊ�½����жϿ�
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{
		PCA3_IO = dirIO;
		PCA3_count = 0;
		CCAPM3 = 0x11;
		CCAP3L = 0;
		CCAP3H = 0; //��չ�ⲿ�˿�CCP3Ϊ�½����жϿ�
	}
	CR = 1; //����PCAʱ��
	EA = 1; //���������ж�
}

int PCA_Count_get(int n) //��ȡĳͨ���������ֵ
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
		break; //�������
	}
	return m;
}

//PCA-PWMģʽ��ʼ������
void PCA_Pwm_init(int pin, int freq, int pwm)
{
	PCA_MODE = 1;			//PCAģʽ����ΪPWMģʽ
	if (pin / 10 % 10 == 1) //PCA�˿��л�
	{
		P_SW1 |= 0x00; //PCAʹ��P14-P17��
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCAʹ��P23-P26��
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCAʹ��P30-P33��
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCAʹ��P70-P73��
	}

	AUXR &= 0x7f; // T0, 12T ģʽ ��ΪPCAʱ��
	TMOD |= 0x02; //��ʱ��0������ʽ2   8λ�Զ���תģʽ
	TH0 = 256 - (int)((Main_Fosc / 12 / 256) / (freq * 4));
	TL0 = TH0;
	TR0 = 1; //��ʱ����ʼ����

	CCON = 0x00;
	CMOD = 0x04; //PCAʱ��Ϊ��ʱ��0�������
	CL = 0x00;
	CH = 0x00;

	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{													  //��չ�ⲿ�˿�CCP0
		CCAPM0 = 0x42;									  //PCAģ��0ΪPWM����ģʽ
		PCA_PWM0 = 0xc0;								  //PCAģ��0���10λPWM
		PCA0_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM0 += PCA0_n / 256 * 4 + PCA0_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP0H = CCAP0L = PCA0_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{													  //��չ�ⲿ�˿�CCP1
		CCAPM1 = 0x42;									  //PCAģ��1ΪPWM����ģʽ
		PCA_PWM1 = 0xc0;								  //PCAģ��1���10λPWM
		PCA1_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM1 += PCA1_n / 256 * 4 + PCA1_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP1H = CCAP1L = PCA1_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{													  //��չ�ⲿ�˿�CCP2
		CCAPM2 = 0x42;									  //PCAģ��2ΪPWM����ģʽ
		PCA_PWM2 = 0xc0;								  //PCAģ��2���10λPWM
		PCA2_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM2 += PCA2_n / 256 * 4 + PCA2_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP2H = CCAP2L = PCA2_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{													  //��չ�ⲿ�˿�CCP3
		CCAPM3 = 0x42;									  //PCAģ��3ΪPWM����ģʽ
		PCA_PWM3 = 0xc0;								  //PCAģ��3���10λPWM
		PCA3_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM3 += PCA3_n / 256 * 4 + PCA3_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP3H = CCAP3L = PCA3_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
	}
	CR = 1; //����PCAʱ��
}

void PCA_Pwm_change(int pin, int pwm) //�ı�PWMռ��
{
	switch (pin)
	{
	case 0:
	{
		PCA_PWM0 = 0xc0;								  //PCAģ��0���10λPWM
		PCA0_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM0 += PCA0_n / 256 * 4 + PCA0_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP0H = CCAP0L = PCA0_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
		break;
	}
	case 1:
	{
		PCA_PWM1 = 0xc0;								  //PCAģ��1���10λPWM
		PCA1_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM1 += PCA1_n / 256 * 4 + PCA1_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP1H = CCAP1L = PCA1_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
		break;
	}
	case 2:
	{
		PCA_PWM2 = 0xc0;								  //PCAģ��2���10λPWM
		PCA2_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM2 += PCA2_n / 256 * 4 + PCA2_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP2H = CCAP2L = PCA2_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
		break;
	}
	case 3:
	{
		PCA_PWM3 = 0xc0;								  //PCAģ��3���10λPWM
		PCA3_n = (int)(((10000 - pwm) / 10000.0) * 1024); //����PWMռ�ճ�ֵ
		PCA_PWM3 += PCA3_n / 256 * 4 + PCA3_n / 256 * 16; //PWMռ�ձ����� ����λ
		CCAP3H = CCAP3L = PCA3_n % 256;					  //PWMռ�ձ����� �Ͱ�λ
		break;
	}
	default:
		break; //�������
	}
}

//PCA��������ģʽ��ʼ������
void PCA_Pulse_init(int pin, unsigned long freq)
{
	PCA_MODE = 2; //PCAģʽ����Ϊ�������ģʽ
	if (pin / 10 % 10 == 1)
	{
		P_SW1 |= 0x00; //PCAʹ��P14-P17��
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCAʹ��P23-P26��
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCAʹ��P30-P33��
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCAʹ��P70-P73��
	}
	CCON = 0x00;
	CMOD = 0x08; //PCAʱ��Ϊϵͳʱ��
	CL = 0x00;
	CH = 0x00;
	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{
		CCAPM0 = 0x4d; //PCAģ��0Ϊ16λ��ʱ��ģʽ��ʹ���������
		PCA0_HZ = Main_Fosc / 2 / freq;
		PCA0_n = PCA0_HZ;
		CCAP0L = PCA0_n;
		CCAP0H = PCA0_n >> 8;
		PCA0_n += PCA0_HZ;
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{
		CCAPM1 = 0x4d; //PCAģ��0Ϊ16λ��ʱ��ģʽ��ʹ���������
		PCA1_HZ = Main_Fosc / 2 / freq;
		PCA1_n = PCA1_HZ;
		CCAP1L = PCA1_n;
		CCAP1H = PCA1_n >> 8;
		PCA1_n += PCA1_HZ;
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{
		CCAPM2 = 0x4d; //PCAģ��0Ϊ16λ��ʱ��ģʽ��ʹ���������
		PCA2_HZ = Main_Fosc / 2 / freq;
		PCA2_n = PCA2_HZ;
		CCAP2L = PCA2_n;
		CCAP2H = PCA2_n >> 8;
		PCA2_n += PCA2_HZ;
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{
		CCAPM3 = 0x4d; //PCAģ��0Ϊ16λ��ʱ��ģʽ��ʹ���������
		PCA3_HZ = Main_Fosc / 2 / freq;
		PCA3_n = PCA3_HZ;
		CCAP3L = PCA3_n;
		CCAP3H = PCA3_n >> 8;
		PCA3_n += PCA3_HZ;
	}
	CR = 1; //����PCAʱ��
	EA = 1; //���������ж�
}

//PCA�����Ȳ�����ʼ������
void PCA_Width_init(int pin)
{
	PCA_MODE = 4; //PCAģʽ����Ϊ�������ģʽ
	if (pin / 10 % 10 == 1)
	{
		P_SW1 |= 0x00; //PCAʹ��P14-P17��
	}
	if (pin / 10 % 10 == 2)
	{
		P_SW1 |= 0x10; //PCAʹ��P23-P26��
	}
	if (pin / 10 % 10 == 3)
	{
		P_SW1 |= 0x30; //PCAʹ��P30-P33��
	}
	if (pin / 10 % 10 == 7)
	{
		P_SW1 |= 0x20; //PCAʹ��P70-P73��
	}
	CCON = 0x00;
	CMOD = 0x00; //PCAʱ��Ϊϵͳʱ��/12 = 2MHZ��һ������0.5us
	CL = 0x00;
	CH = 0x00;
	if ((pin / 10 % 10 == 7 && pin % 10 == 0) || (pin / 10 % 10 == 1 && pin % 10 == 7) || (pin / 10 % 10 == 2 && pin % 10 == 3) || (pin / 10 % 10 == 3 && pin % 10 == 3))
	{
		PCA0_IO = pin;
		PCA0_n = 0;		 //����ֵ��0
		CCAPM0 = 0x31;	 //PCAģ���������½��ض��жϣ��������ж�
		PCA_PWM0 = 0x00; //8λPWM��ȣ�û�ã�
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 1) || (pin / 10 % 10 == 1 && pin % 10 == 6) || (pin / 10 % 10 == 2 && pin % 10 == 4) || (pin / 10 % 10 == 3 && pin % 10 == 2))
	{
		PCA1_IO = pin;
		PCA1_n = 0;		 //����ֵ��0
		CCAPM1 = 0x31;	 //PCAģ���������½��ض��жϣ��������ж�
		PCA_PWM1 = 0x00; //8λPWM��ȣ�û�ã�
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 2) || (pin / 10 % 10 == 1 && pin % 10 == 5) || (pin / 10 % 10 == 2 && pin % 10 == 5) || (pin / 10 % 10 == 3 && pin % 10 == 1))
	{
		PCA2_IO = pin;
		PCA2_n = 0;		 //����ֵ��0
		CCAPM2 = 0x31;	 //PCAģ���������½��ض��жϣ��������ж�
		PCA_PWM2 = 0x00; //8λPWM��ȣ�û�ã�
	}
	if ((pin / 10 % 10 == 7 && pin % 10 == 3) || (pin / 10 % 10 == 1 && pin % 10 == 4) || (pin / 10 % 10 == 2 && pin % 10 == 6) || (pin / 10 % 10 == 3 && pin % 10 == 0))
	{
		PCA3_IO = pin;
		PCA3_n = 0;		 //����ֵ��0
		CCAPM3 = 0x31;	 //PCAģ���������½��ض��жϣ��������ж�
		PCA_PWM3 = 0x00; //8λPWM��ȣ�û�ã�
	}
	CR = 1; //����PCAʱ��
	EA = 1; //���������ж�
}

uint PCA_Width_get(int pin) //��ȡĳͨ��������
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
		break; //�������
	}
	return m;
}