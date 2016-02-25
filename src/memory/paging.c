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
extern uint32 PAGE_TABLE_KERNEL[];
void paging_setDirectory( uint32* pDirectory );
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

void paging_cloneTable( uint32 nOld, uint32 nNew )
{
    ASSERT( nOld < PAGE_DIR_ENTRIES );
    ASSERT( nNew < PAGE_DIR_ENTRIES );

    PAGE_DIRECTORY[nNew] = PAGE_DIRECTORY[nOld];
}

void paging_init( )
{
    // Set up a table containing the first 4 MB of memory
    
    uint32 pIdentityTable = (uint32)PAGE_TABLE_KERNEL - PAGING_KERNEL_OFFSET;

    for ( uint32 i=0; i < 1024; i++ )
    {
        set_dword( pIdentityTable + i*4, i * 0x1000 | PAGE_PRESENT | PAGE_WRITABLE | PAGE_KERNELMODE );
    }

    // Map our new table to first 4 MB and at 3 GB
    
    uint32 pDirectory = (uint32)PAGE_DIRECTORY - PAGING_KERNEL_OFFSET;
    uint32 nEntry = (pIdentityTable & 0xFFFFF800) | (PAGE_PRESENT | PAGE_WRITABLE | PAGE_KERNELMODE);

    set_dword( pDirectory, nEntry );
    set_dword( pDirectory + (768*4), nEntry );
    
    // Give our directory to the processor
    
    paging_setDirectory( PAGE_DIRECTORY - PAGING_KERNEL_OFFSET );

    // Enable PAE if we want it (not implemented yet)
    
    if ( PAGING_PAE_ENABLED )
        paging_enablePAE( );

    // Enable paging
    
    paging_enable( );
}
