#include "config.h"

extern void ADC_init(int pin, int speed); //ADת����ʼ������
/*
ȡֵ��pin:Ҫ��ʼ��ͨ��     ����0 Ϊ P1^0��ADCͨ��0	ȡֵ��Χ��0,1,2,3,4,5,6,7
ȡֵ��speed:ADת���ٶ�     ȡֵ��Χ��1-16   ȡֵԽ��ת���ٶ�Խ�죬���ɴ�80���/ÿ��
*/
extern int ADC_get(int pin); //��ȡADCת���������
/*
ȡֵ��pin:Ҫ��ʼ��ͨ��     ����0 Ϊ P1^0��ADCͨ��0	ȡֵ��Χ��0-7
*/
