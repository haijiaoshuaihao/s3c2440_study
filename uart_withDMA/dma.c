#include "s3c2440_soc.h"
#include "uart.h"
char *SendBuffer = "Hello mini2440!"; //source data

unsigned int * p = (unsigned int *) (0x50000020);

void dma_init(const char *s)
{
   // DISRC0 = (unsigned int)SendBuffer;
   unsigned int size = mystrlen(s);
   DISRC0 = (unsigned int)s;
   DISRCC0 &= ~(3 << 0);
   DIDST0 = (unsigned int)(0x50000020);
   DIDSTC0 |= ((0 << 2) | (1 << 1) | (1 << 0));
   DCON0 |= ((1 << 31) | (0 << 30) | (1 << 29) | (0 << 28) |
             (0 << 27) | (1 << 24) | (1 << 23) | (1 << 22) | (0 << 20)| size);
   DMASKTRIG0 |= ((0 << 2) | (1 << 1) | (0 << 0));
   INTMSK &= ~(1 << 17);
}