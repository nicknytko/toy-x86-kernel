#include <base.h>

#include "paging.h"
#include "pool.h"
#include "heap.h"

static s_poolHeader* pPool;

void kheap_init( )
{
    pPool = pool_init( KHEAP_PHYSICAL_START + PAGING_KERNEL_OFFSET,
                       KHEAP_PHYSICAL_END + PAGING_KERNEL_OFFSET );
}

void* kmalloc( uint32 nSize )
{
    return pool_malloc( pPool, nSize );
}

void* kmalloc_a( uint32 nSize, uint32 nAlignment )
{
    return pool_malloca( pPool, nSize, nAlignment );
}

void kfree( void* pBlock )
{
    pool_free( pPool, pBlock );
}

void kheap_debugPrint( )
{
    pool_debugPrint( pPool );
}
