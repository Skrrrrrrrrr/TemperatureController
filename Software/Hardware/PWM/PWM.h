#include "config.h"

extern unsigned int PWM0_T; 
extern unsigned int PWM1_T; 
extern unsigned int PWM2_T; 
extern unsigned int PWM3_T; 
extern unsigned int PWM4_T; 
extern unsigned int PWM5_T; 
extern unsigned int PWM6_T; 
extern unsigned int PWM7_T; 
extern unsigned char STORE; 

extern void PWM_init(int pin,long f,int pwm); //PWMģ���ʼ������
/*
ȡֵ��pin:Ҫ��ʼ�������Ŷ˿� ����10 Ϊ ����Ӧ��PWMͨ����ʼ����P10�ڶ�Ӧ����
														     22 Ϊ ����Ӧ��PWMͨ����ʼ����P22�ڶ�Ӧ���� 
																 64 Ϊ ����Ӧ��PWMͨ����ʼ����P64�ڶ�Ӧ����
													   ע�⣺STC8��Ƭ������P1,P2,P6�ھ���PWM���ܣ����ܳ�ʼ���������˿ڵ�����
ȡֵ��f:PWM���Ƶ��        ����  ȡֵ��Χ��50Hz-100KHz   
													 ע�⣺����PWMͨ�����뱣֤Ƶ��һ�¡�Ƶ��ȡֵԽ��PWM����Խ��׼ȷ��100KHzʱPWM���ھ���Ϊ7.25%�����ϴ�
ȡֵ��pwm:PWM��ʼռ�ձ�    ȡֵ��Χ�� 0-10000   ��Ӧ 0%-100%
*/
extern void PWM_change(int pin,int pwm); //�ı�PWMģ���ռ�ձ�
/*
ȡֵ��pin:Ҫ�ı��ͨ��     ����  10 Ϊ ��P10�˿ڶ�Ӧ��PWMͨ���ı�
														     22 Ϊ ��P22�˿ڶ�Ӧ��PWMͨ���ı�
																 64 Ϊ ��P64�˿ڶ�Ӧ��PWMͨ���ı� 
ȡֵ��pwm:�µ�PWMռ�ձ�    ȡֵ��Χ�� 0-10000   ��Ӧ 0%-100%
*/