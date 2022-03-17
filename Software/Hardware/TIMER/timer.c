#include "timer.h"

/***************************************************************/
//初始化的initValue为通讯波特率
/***************************************************************/

u16 timer2Cnt = 0;
u16 timer4Cnt = 0;

extern u8 wptr;
u8 *pWptr = &wptr;
extern SqQueue sq;
extern SqQueue nDataCntSq;
extern DataStateEnum dataState;
extern u8 rxBuffer[MAXMODBUSDATALENGTH];
extern u8 *pRxBuffer;

// void Timer0_init(bool irtEn, u32 initValue, u8 TMode, bool T0_1T, bool clkoutEn)
// {
//     TR0 = 0; //停止计数

//     ET0 = irtEn;

//     TMOD |= TMode;
//     AUXR |= ((u8)T0_1T) << 6;                  //T12_1=0,12T;T12_1=1,1T
//     TL0 = (65536 - Main_Fosc / initValue / 4); //定时器1装初值
//     TH0 = (65536 - Main_Fosc / initValue / 4) >> 8;

//     if (clkoutEn)
//     {
//         INT_CLKO |= 0x01; //输出时钟
//     }
//     else
//     {
//         INT_CLKO &= 0xfe; //不输出时钟
//     }
//     TR0 = 1; //使能计数
// }

void Timer1_init(bool irtEn, u32 initValue, u8 TMode, bool T1_1T, bool clkoutEn)
{
    TR1 = 0; //停止计数

    ET1 = irtEn;

    TMOD |= TMode;
    AUXR |= ((u8)T1_1T) << 6;                  //T12_1=0,12T;T12_1=1,1T
    TL1 = (65536 - Main_Fosc / initValue / 4); //定时器1装初值
    TH1 = (65536 - Main_Fosc / initValue / 4) >> 8;

    if (clkoutEn)
    {
        INT_CLKO |= 1 << 1; //输出时钟
    }
    else
    {
        INT_CLKO &= ~(0 << 1); //不输出时钟
    }

    TR1 = 1; //使能计数
}

void Timer2_init(bool irtEn, u32 initValue, u8 TMode, bool T2_1T, bool clkoutEn)
{
    AUXR &= ~0x1c; //停止计数, 定时模式, 12T模式
    if (irtEn)
    {
        IE2 |= ET2; //允许中断
    }
    else
    {
        IE2 &= ~ET2; //
    }

    TMOD |= TMode;
    T4T3M |= (((u8)T2_1T) << 1);               //1T mode
    T2L = (65536 - Main_Fosc / initValue / 4); //定时器2装初值，固定为16位重载模式
    T2H = (65536 - Main_Fosc / initValue / 4) >> 8;

    // INT_CLKO &= ((u8)irtEn) << 4 | 0xef;
    if (clkoutEn)
    {
        INT_CLKO |= 0x04; //输出时钟
    }
    else
    {
        INT_CLKO &= ~0x04; //不输出时钟
    }
    AUXR |= (1 << 4); //开始运行
}

void Timer3_init(bool irtEn, u32 initValue, bool T3_1T, bool clkoutEn)
{
    T4T3M &= ~0x0f; //停止计数
    if (irtEn)
    {
        IE2 |= ET3; //允许中断
    }
    else
    {
        IE2 &= ~ET3;
    }

    T4T3M |= (((u8)T3_1T) << 1); //1T mode

    T3L = (65536 - Main_Fosc / initValue / 4); //定时器3装初值，固定为16位重载模式
    T3H = (65536 - Main_Fosc / initValue / 4) >> 8;

    // INT_CLKO &= ((u8)irtEn) << 5 | 0xDf;

    if (clkoutEn)
    {
        T4T3M |= 0x01; //输出时钟
    }
    else
    {
        T4T3M &= ~0x01; //不输出时钟
    }
    T4T3M |= (1 << 3); //使能计数
}

void Timer4_init(bool irtEn, u32 initValue, bool T4_1T, bool clkoutEn)
{
    T4T3M &= ~0xf0; //停止计数, 定时模式, 12T模式, 不输出时钟
    if (irtEn)
    {
        IE2 |= ET4; //允许中断
    }
    else
    {
        IE2 &= ~ET4;
    }

    T4T3M |= (((u8)T4_1T) << 1); //1T mode

    T4L = (65536 - Main_Fosc / initValue / 4); //定时器4装初值。固定为16位重载模式
    T4H = (65536 - Main_Fosc / initValue / 4) >> 8;

    // INT_CLKO &= ((u8)irtEn) << 6 | 0xBf;

    if (clkoutEn)
    {
        T4T3M |= 0x10; //输出时钟
    }
    else
    {
        T4T3M &= ~0x10; //不输出时钟
    }
    T4T3M |= (1 << 7); //开始运行
}

void Timer3_start(void)
{
    T4T3M |= (1 << 3); //使能计数
}
void Timer3_stop(void)
{
    T4T3M &= ~0x0f; //停止计数
}
void Timer4_start(void)
{
    T4T3M |= (1 << 7); //开始运行
}
void Timer4_stop(void)
{
    T4T3M &= ~0xf0; //停止计数
}
// //========================================================================
// // 函数: void timer0Isr (void) interrupt TIMER0_VECTOR
// // 描述:  timer0中断函数.
// // 参数: none.
// // 返回: none.
// // 版本: V1.0, 2015-1-12
// //========================================================================
// void timer0Isr(void) interrupt TIMER0_VECTOR
// {
// }

//========================================================================
// 函数: void timer1Isr (void) interrupt TIMER1_VECTOR
// 描述:  timer1中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
// void timer1Isr(void) interrupt TIMER1_VECTOR
// {
//     DacSDI = ~DacSDI;
// }

//========================================================================
// 函数: void timer2Isr (void) interrupt TIMER2_VECTOR
// 描述:  timer2中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer2Isr(void) interrupt TIMER2_VECTOR
{

    if (timer2Cnt++ > 100)
    {
        timer2Cnt = 0;
        if (++dacChn >= MAXAD7124CHNS)
        {
            dacChn = 0;
        }
    }
}

//========================================================================
// 函数: void timer3Isr (void) interrupt TIMER3_VECTOR
// 描述:  timer3中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer3Isr(void) interrupt TIMER3_VECTOR
{
    modbusDataGapCnt++;
    if (modbusDataGapCnt > MODBUS_T_x_CNT(3.5))
    {
        dataState = IS_ADDR;
        Timer3_stop();
        return;
    }

    if (modbusDataGapCnt > MODBUS_T_x_CNT(1.5))
    {
        dataState = IS_IDLE;
        if (wptr == 0) //消除modbusDataGapCnt在1.5和3.5字符时间之间重复跑下面的程序段，节省指针pRxBuffer定向和memset的时间（大约30ms）
        {
            return;
        }
        if (wptr > 7) //进入这个逻辑的是有效数据超过7个（wptr++不含地址），认为这wptr个数据是有效的（但未经crc）
        {
            EnQueue(&sq, rxBuffer, wptr);
            EnQueue(&nDataCntSq, pWptr, 1);
        }
        pRxBuffer = rxBuffer;
        memset(pRxBuffer, 0, wptr);
        wptr = 0;
    }
}

//========================================================================
// 函数: void timer4Isr (void) interrupt TIMER4_VECTOR
// 描述:  timer4中断函数.
// 参数: none.
// 返回: none.
// 版本: V1.0, 2015-1-12
//========================================================================
void timer4Isr(void) interrupt TIMER4_VECTOR
{
    timer4Cnt++;
    if (timer4Cnt == ADCSETUPTIME) //80ms
    {
        timer4Cnt = 0;
        IE1 = 0; //清INT1标志位
        EX1 = 1; //INT1中断开
        P10 = ~P10;
    }
}
