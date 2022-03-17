#include "DAC7611.h"

void DAC(u16 dat)
{
    u8 nCLK = 0;
    DacLD = 1;
    N_NOP(4);
    DacCS = 0;
    N_NOP(2);
    // DacCLK = 0;
    // N_NOP(4);
    for (nCLK; nCLK < 12; nCLK++)
    {
        DacCLK = 0;
        N_NOP(4);
        if (dat & 0x800)
        {
            DacSDI = 1;
        }
        else
        {
            DacSDI = 0;
        }
        dat <<= 1;
        N_NOP(1);
        DacCLK = 1;
        N_NOP(4);
    }
    DacCLK = 1;
    N_NOP(4);
    DacCS = 1;
    N_NOP(4);
    DacLD = 0;
    N_NOP(16);
    DacLD = 1;
    N_NOP(16);
    DacLD = 0;
}
void N_NOP(u16 n)
{
    while (n--)
    {
        _nop_();
    }
}
