#include "fifoqueue.h"

// //Queue Init
// void QueueInit(struct FifoQueue *queue)
// {
//     queue.front = queue.rear; //初始化时队列头队列首相连
//     queue.count = 0;           //队列计数为0
// }

// // Queue In
// u8 QueueIn(struct FifoQueue *queue, ElemType sdat) //数据进入队列
// {
//     if ((queue.front == queue.rear) && (queue.count == QueueSize))
//     {                     // full //判断如果队列满了
//         return QueueFull; //返回队列满的标志
//     }
//     else
//     { // in
//         queue.dat[queue.rear] = sdat;
//         queue.rear = (queue.rear + 1) % QueueSize;
//         queue.count = queue.count + 1;
//         return QueueOperateOk;
//     }
// }

// // Queue Out
// u8 QueueOut(struct FifoQueue *queue, ElemType *sdat)
// {
//     if ((queue.front == queue.rear) && (queue.count == 0))
//     { // empty
//         return QueueEmpty;
//     }
//     else
//     { // out
//         *sdat = queue.dat[queue.front];
//         queue.front = (queue.front + 1) % QueueSize;
//         queue.count = queue.count - 1;
//         return QueueOperateOk;
//     }
// }

//-----循环队列的基本操作的算法描述-----
void QueueInit(SqQueue *sq)
{
    //构造一个空队列Q
    // sq->base = (u8 *)malloc(MAXQUEUESIZE * sizeof(u8));
    memset(sq->base, '\0', MAXQUEUESIZE * sizeof(u8));
    // if (!sq->base)
    //     return OVERFLOW; // 存储分配失败
    sq->front = 0;
    sq->rear = 0;
}
int GetQueueLength(SqQueue *sq)
{
    //返回sq的元素个数，即队列的长度
    return (MAXQUEUESIZE - sq->front + sq->rear) % MAXQUEUESIZE;
}
void EnQueue(SqQueue *sq, u8 *ch, u8 len)
{
    u8 enCnt = 0;
    //插入元素ch为sq的新的队尾元素
    if ((sq->rear + 1) % MAXQUEUESIZE == sq->front)
        return; // 队列满
    while (enCnt < len)
    {
        sq->base[sq->rear++] = ch[enCnt++];
        if (sq->rear == MAXQUEUESIZE) //如果MAXQUEUESIZE=256，可以省略此函数段
        {
            sq->rear = 0;
        }
    }
    // while (enCnt < len)
    // {
    //     sq->base[sq->rear + enCnt] = ch[enCnt];
    //     enCnt++;
    // }

    // // sq->base += ch;
    // sq->rear = (sq->rear + len) % MAXQUEUESIZE;
}
void DeQueue(SqQueue *sq, u8 **ch, u8 len)
{
    u8 deCnt = 0;
    if (sq->front == sq->rear)
        return;
    while (deCnt < len)
    {
        *(*ch + deCnt) = sq->base[sq->front++];
        deCnt++;
        if (sq->front == MAXQUEUESIZE) //如果MAXQUEUESIZE=256，可以省略此函数段
        {
            sq->front = 0;
        }
    }
    // while (deCnt < len)
    // {
    //     *(*ch + deCnt) = sq->base[sq->front + deCnt];
    //     deCnt++;
    // }

    // sq->front = (sq->front + len) % MAXQUEUESIZE;
}
