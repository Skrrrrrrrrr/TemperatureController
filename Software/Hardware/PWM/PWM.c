/**********************************************************
    ��������Ĵ��ĵ�����غ���������鿴���ͷ�ļ�����
**********************************************************/
#include "PWM.h"

unsigned int PWM0_T; 
unsigned int PWM1_T; 
unsigned int PWM2_T; 
unsigned int PWM3_T; 
unsigned int PWM4_T; 
unsigned int PWM5_T; 
unsigned int PWM6_T; 
unsigned int PWM7_T; 
unsigned char STORE;

void PWM_init(int pin,long f,int pwm)  //PWM��ʼ������
{
	switch(pin%10)
	{
		case 0:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==10) PWM0CR=0x08;
			if(pin==20) PWM0CR=0x00;
			if(pin==60) PWM0CR=0x10;
			PWM0_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM0_T;                        //����PWM����ʱ����
			PWM0T1= (long)pwm*PWM0_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM0T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM0CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
		case 1:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==11) PWM1CR=0x08;
			if(pin==21) PWM1CR=0x00;
			if(pin==61) PWM1CR=0x10;
			PWM1_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM1_T;                        //����PWM����ʱ����
			PWM1T1= (long)pwm*PWM1_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM1T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM1CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
		case 2:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==12) PWM2CR=0x08;
			if(pin==22) PWM2CR=0x00;
			if(pin==62) PWM2CR=0x10;
			PWM2_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM2_T;                        //����PWM����ʱ����
			PWM2T1= (long)pwm*PWM2_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM2T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM2CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
		case 3:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==13) PWM3CR=0x08;
			if(pin==23) PWM3CR=0x00;
			if(pin==63) PWM3CR=0x10;
			PWM3_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM3_T;                        //����PWM����ʱ����
			PWM3T1= (long)pwm*PWM3_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM3T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM3CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
		case 4:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==14) PWM4CR=0x08;
			if(pin==24) PWM4CR=0x00;
			if(pin==64) PWM4CR=0x10;
			PWM4_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM4_T;                        //����PWM����ʱ����
			PWM4T1= (long)pwm*PWM4_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM4T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM4CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
		case 5:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==15) PWM5CR=0x08;
			if(pin==25) PWM5CR=0x00;
			if(pin==65) PWM5CR=0x10;
			PWM5_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM0_T;                        //����PWM����ʱ����
			PWM5T1= (long)pwm*PWM5_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM5T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM5CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
		case 6:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==16) PWM6CR=0x08;
			if(pin==26) PWM6CR=0x00;
			if(pin==66) PWM6CR=0x10;
			PWM6_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM6_T;                        //����PWM����ʱ����
			PWM6T1= (long)pwm*PWM6_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM6T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM6CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
		case 7:
		{
			//STORE=P_SW2;
			P_SW2 |= 0x80; //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
			
			PWMCKS = 0x0f;                              // PWMʱ��Ϊϵͳʱ��/16 ,����Ӧ��ͬPWMƵ�ʡ�   
			PWMCFG = 0x00;  											//PWM���üĴ�����PWM���жϣ�PWM����ADC���� 
			if(pin==17) PWM7CR=0x08;
			if(pin==27) PWM7CR=0x00;
			if(pin==67) PWM7CR=0x10;
			PWM7_T = Main_Fosc16/f;                   //����PWMһ��������������
			PWMC = PWM7_T;                        //����PWM����ʱ����
			PWM7T1= (long)pwm*PWM7_T/10000;              //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
			PWM7T2= 0;                             //PWM0�ڼ���ֵΪ700H�ط�����ߵ�ƽ
			 
			PWM7CR|=0x80;                          //ʹ��PWM���
			P_SW2  &= ~0x80;                       //PSW2�Ĵ������λ��0   
			PWMCR  |= 0x80;   //ʹ��PWM���η�������PWM��������ʼ����
			break;   //PWM0
		}
	}

	
}

void PWM_change(int pin,int pwm)    //�ı�PWMģ��ռ�ձ�
{
	//STORE=P_SW2;
	P_SW2 |= 0x80;  //���¼Ĵ���Ϊ��չsfr,����ǰ���Ƚ�PSW2�Ĵ������λ��1
	switch(pin%10)
	{
		case 0:	PWM0T1= (long)pwm*PWM0_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
		case 1:	PWM1T1= (long)pwm*PWM1_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
		case 2:	PWM2T1= (long)pwm*PWM2_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
		case 3:	PWM3T1= (long)pwm*PWM3_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
		case 4:	PWM4T1= (long)pwm*PWM4_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
		case 5:	PWM5T1= (long)pwm*PWM5_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
		case 6:	PWM6T1= (long)pwm*PWM6_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
		case 7:	PWM7T1= (long)pwm*PWM7_T/10000;        //PWM0�ڼ���ֵΪ100H�ط�����͵�ƽ
						break;
	}
	P_SW2  &= ~0x80;  //���ϼĴ���Ϊ��չsfr,���ʺ��轫PSW2�Ĵ������λ��0
}