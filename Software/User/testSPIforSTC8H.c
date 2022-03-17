#include "config.h"

fine : master undefine : slave

#define SPIF 0x80 //SPI传输完成标志。写入1清0。
#define WCOL 0x40 //SPI写冲突标志。写入1清0。
// sbit P57 = P5 ^ 7;
///////////////////////////////////////////////////////////////
#define SPI_IO_P12P13P14P15 0xFF & (0 << 2)
#define SPI_IO_P54P13P14P15 0xFF & (0 << 2)
#define SPI_IO_P22P23P24P25 0xFF & (1 << 2)
#define SPI_IO_P54P40P41P43 0xFF & (2 << 2)
#define SPI_IO_P35P34P33P32 0xFF & (3 << 2)

///////////////////////////////////////////////////////////////
// sfr AUXR = 0x8e; //Auxiliary register
// sfr SPSTAT = 0x84;   //SPI status register
#define SPIF 0x80 //SPSTAT.7
#define WCOL 0x40 //SPSTAT.6
// sfr SPCTL = 0x85;    //SPI control register
#define SSIG 0x80  //SPCTL.7
#define SPEN 0x40  //SPCTL.6
#define DORD 0x20  //SPCTL.5
#define MSTR 0x10  //SPCTL.4
#define CPOL 0x08  //SPCTL.3
#define CPHA 0x04  //SPCTL.2
#define SPDHH 0x00 //CPU_CLK/4
#define SPDH 0x01  //CPU_CLK/16
#define SPDL 0x02  //CPU_CLK/64
#define SPDLL 0x03 //CPU_CLK/128                                    \
                   // sfr SPDAT = 0x86;    //SPI data register      \
                   // sbit SPISS = P1 ^ 4;                          \
                   // sbit MISO = P1 ^ 6; //SPI DOUT,low when ready \
                   ///////////////////////////////////
                         ;
sbit SS = P35;
sbit testIO = P10;

bit busy;

void SPI_Isr() interrupt 9
{
    SPSTAT = 0xc0;
    SS = 1;
    busy = 0;
    testIO = ~testIO;
}

void main()
{

    InitIO();

    testIO = 1;
    SS = 1;
    busy = 0;

    SPCTL = 0x50;
    SPSTAT = 0xc0;
    IE2 |= ESPI;
    EA = 1;
    while (1)
    {
        while (busy)
            ;
        busy = 1;
        SS = 0;
        SPDAT = 0x5a;
    }
}