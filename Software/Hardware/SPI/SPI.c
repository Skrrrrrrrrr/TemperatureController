#include "SPI.h"

void SpiInit()
{
    SPDAT = 0;            //initial SPI data
    SPSTAT = SPIF | WCOL; //clear SPI status
#ifdef MASTER
    SPCTL = SSIG | SPEN | MSTR;  //master mode
    SPCTL = SPCTL | CPHA | CPOL; //
    SPCTL = SPCTL | SPDL;        //SPI BAUD
#else
    SPCTL = SPEN; //slave mode
#endif
    // SPCTL |= (1 << 7);                   //忽略 SS 引脚功能，使用 MSTR 确定器件是主机还是从机
    // SPCTL |= (1 << 6);                   //使能 SPI 功能
    // SPCTL &= ~(1 << 5);                  //先发送/接收数据的高位（ MSB）
    P_SW1 |= SPI_IO_P35P34P33P32; //IO口切换. 0: P1.2/P5.4 P1.3 P1.4 P1.5, 1: P2.2 P2.3 P2.4 P2.5, 2: P5.4 P4.0 P4.1 P4.3, 3: P3.5 P3.4 P3.3 P3.2

    // SPCTL = 0xdc;
    // SPSTAT = 0xc0;
    // // IE2 |= ESPI;
    // P_SW1 |= SPI_IO_P35P34P33P32;
    // SPSTAT = SPIF + WCOL; //清0 SPIF和WCOL标志
}

///////////////////////////////////////////////////////////
//查询方式
u8 spi_write_read(u8 dat)
{
    // #ifdef MASTER
    //     SPISS = 0; //pull low slave SS
    // #endif
    SPDAT = dat; //trigger SPI send
    while (!(SPSTAT & SPIF))
        ;                 //wait send complete
    SPSTAT = SPIF | WCOL; //clear SPI status
    // #ifdef MASTER
    //     SPISS = 1; //push high slave SS
    // #endif
    return SPDAT; //return received SPI data
}

// u16 spi_write_read_u16(u16 dat)
// {
//     u16 ret;
//     ret = SPISwap(dat & 0xff);
//     ret << 8;
//     ret |= SPISwap(dat >> 8 & 0xff);

//     return ret;
// }

// 中断方式
// void spi_isr() interrupt 9
// {
//     SPSTAT = SPIF | WCOL; //clear SPI status
// }
