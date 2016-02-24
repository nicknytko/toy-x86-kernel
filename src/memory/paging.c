#include <base.h>
#include "paging.h"
#include "heap.h"

#include "panic/panic.h"

#define PAGING_PAE_ENABLED	0

#if (PAGING_PAE_ENABLED==1)
#define PAGE_DIR_ENTRIES	512
#else
#define PAGE_DIR_ENTRIES	1024
#endif

// defined in paging_asm.s

extern uint32 PAGE_DIRECTORY[];
void paging_setDirectory( uint32 pDirectory );
void paging_enablePAE( );
void paging_enable( );

void paging_setTable( uint32 nIndex, uint32 pAddress, uint8 nFlags )
{
    ASSERT( nIndex < PAGE_DIR_ENTRIES );

    PAGE_DIRECTORY[nIndex] = ( pAddress & 0xFFFFF800 ) | nFlags;
}

void paging_removeTable( uint32 nIndex )
{
    ASSERT( nIndex < PAGE_DIR_ENTRIES );

    PAGE_DIRECTORY[nIndex] = 0;
}

static void paging_clearDirectory( )
{
    for ( uint32 i=0; i < 1024; i++ )
    {
        paging_setTable( i, 0, PAGE_WRITABLE | PAGE_EMPTY | PAGE_KERNELMODE );
    }
}

void paging_init( )
{
    // Clear the page directory to make sure it has no entries
    paging_clearDirectory( );

    // Identity map (1:1) the first 4 MB
    
    uint32* pIdentityTable = (uint32*)kmalloc_a( 1024 * sizeof(uint32) );

    for ( uint32 i=0; i < 1024; i++ )
    {
        pIdentityTable[i] = i * 0x1000 | PAGE_PRESENT | PAGE_WRITABLE | PAGE_KERNELMODE ;
    }

    // Put our identity-map table in the directory as the first entry
    
    paging_setTable( 0, (uint32)pIdentityTable, PAGE_PRESENT | PAGE_WRITABLE | PAGE_KERNELMODE );

    // Give our directory to the processor
    
    paging_setDirectory( (uint32)&PAGE_DIRECTORY );

    // Enable PAE if we want it
    
    if ( PAGING_PAE_ENABLED )
        paging_enablePAE( );

    // Enable paging
    
    paging_enable( );
}
