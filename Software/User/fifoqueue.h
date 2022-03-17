#ifndef _FIFOQUEUE_H
#define _FIFOQUEUE_H

#include "config.h"

//-----循环队列———队列的顺序存储结构-----
#define MAXQUEUESIZE 256 //最大队列长度，跟u8对应，保证255+1=0，进入循环

typedef struct
{
    u8 base[MAXQUEUESIZE]; //初始化的动态非配存储空间
    u8 front;              //头指针，若队列不空，指向队列的头元素 u8=255+1s时置零
    u8 rear;               //尾指针，若队列不空，指向队列尾元素的下一个位置
} SqQueue;

//-----循环队列的基本操作的算法描述-----
void QueueInit(SqQueue *sq);
int GetQueueLength(SqQueue *sq);
void EnQueue(SqQueue *sq, u8 *ch, u8 len);
void DeQueue(SqQueue *sq, u8 **ch, u8 len);

#endif