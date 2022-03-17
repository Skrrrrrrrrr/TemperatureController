
#ifndef __SPI_H
#define __SPI_H

#include "config.h"

#define MASTER //define:master undefine:slave

#define SPIF 0x80 //SPI传输完成标志。写入1清0。
#define WCOL 0x40 //SPI写冲突标志。写入1清0。

///////////////////////////////////////////////////////////////
#define SPI_IO_P12P13P14P15 (0 << 2)
#define SPI_IO_P54P13P14P15 (0 << 2)
#define SPI_IO_P22P23P24P25 (1 << 2)
#define SPI_IO_P54P40P41P43 (2 << 2)
#define SPI_IO_P35P34P33P32 (3 << 2)

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
#define SPDH 0x01  //CPU_CLK/8
#define SPDL 0x02  //CPU_CLK/16
#define SPDLL 0x03 //CPU_CLK/32

void SpiInit(void);
u8 spi_write_read(u8 dat); //swap SPI data between master and slave
// u16 spi_write_read_u16(u16 dat);

#endif