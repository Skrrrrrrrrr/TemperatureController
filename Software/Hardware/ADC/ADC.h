#include "config.h"

extern void ADC_init(int pin, int speed); //AD转换初始化函数
/*
取值：pin:要初始化通道     例：0 为 P1^0，ADC通道0	取值范围：0,1,2,3,4,5,6,7
取值：speed:AD转换速度     取值范围：1-16   取值越大，转换速度越快，最快可达80万次/每秒
*/
extern int ADC_get(int pin); //获取ADC转换结果函数
/*
取值：pin:要初始化通道     例：0 为 P1^0，ADC通道0	取值范围：0-7
*/
