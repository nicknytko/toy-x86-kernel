#include <base.h>
#include "bda.h"

#include <memory/paging.h>

uint8 bda_numSerialPorts( )
{
    uint8 nMask = (get_word( PAGING_KERNEL_OFFSET + BDA_EQUIPMENT ) & 0xF00) >> 8;

    switch (nMask)
    {
    default:
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 4:
        return 3;
    case 8:
        return 4;
    }
}

uint8 bda_numParallelPorts( )
{
    uint8 nMask = (get_word( PAGING_KERNEL_OFFSET + BDA_EQUIPMENT ) & 0xC000) >> 14;

    switch (nMask)
    {
    default:
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    case 4:
        return 3;
    }
}

uint16 bda_serial1Port( )
{
    return get_word( PAGING_KERNEL_OFFSET + BDA_SERIAL1_PORT );
}

uint16 bda_serial2Port( )
{
    return get_word( PAGING_KERNEL_OFFSET + BDA_SERIAL2_PORT );
}

uint16 bda_serial3Port( )
{
    return get_word( PAGING_KERNEL_OFFSET + BDA_SERIAL3_PORT );
}

uint16 bda_serial4Port( )
{
    return get_word( PAGING_KERNEL_OFFSET + BDA_SERIAL4_PORT );
}

uint16 bda_parallel1Port( )
{
    return get_word( PAGING_KERNEL_OFFSET + BDA_PARALLEL1_PORT );
}

uint16 bda_parallel2Port( )
{
    return get_word( PAGING_KERNEL_OFFSET + BDA_PARALLEL2_PORT );
}

uint16 bda_parallel3Port( )
{
    return get_word( PAGING_KERNEL_OFFSET + BDA_PARALLEL3_PORT );
}
