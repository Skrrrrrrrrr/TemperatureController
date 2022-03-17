#ifndef __SYS_H
#define __SYS_H

#include "config.h"
#define true 1
#define false 0
#define ENABLE 1
#define DISABLE 0
/**********************************************************************/
// typedef unsigned char u8;
// typedef unsigned int u16;
// typedef unsigned long u32;

typedef bit bool;

//自定义float类型，方便串口将数据传出
typedef union
{
    u8 uData[4];
    float fData;
} MyFloat;

#endif