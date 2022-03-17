#ifndef __CRC_H
#define __CRC_H
//CRC16-IBM:X16+X15+X2+X1
#include "config.h"

const u8 auchCRCHi[];

const u8 auchCRCLo[];

u16 CRC16(u8 *msg, u8 length);
// u16 CRC16(u8 *frame, u8 len);
#endif