#include <base.h>

extern uint32 end;
static uint32 pHeapAddress;
static uint32 pHeapBase;

void kheap_init( )
{
    pHeapAddress = end;
    pHeapBase = end;
}

uint32 kmalloc( uint32 nSize )
{
    uint32 pTemp = pHeapAddress;
    pHeapAddress += nSize;

    return pTemp;
}

uint32 kmalloc_a( uint32 nSize )
{
    uint32 pTemp = (pHeapAddress & 0xFFFFF000) + 0x1000;
    pHeapAddress = pTemp + nSize;

    return pTemp;
}
