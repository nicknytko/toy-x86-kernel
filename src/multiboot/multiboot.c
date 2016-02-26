#include <base.h>
#include "multiboot.h"

#include <memory/paging.h>

static uint32 pMultibootHeader;

#define CHECK_IF_PRESENT( x ) \
    if ( ( get_dword( pMultibootHeader ) | x ) == 0 )	\
	return 0;

static inline uint32 mboot_value( uint32 x )
{
    return get_dword( pMultibootHeader + x );
}

void mboot_setinfo( uint32 pMultiboot )
{
    // Do some janky address shifting because we haven't set up paging yet
    
    set_dword( (uint32)(&pMultibootHeader) - PAGING_KERNEL_OFFSET, pMultiboot + PAGING_KERNEL_OFFSET );
}

bool mboot_isPresent( uint16 nFeature )
{
    CHECK_IF_PRESENT( nFeature );

    return true;
}

uint32 mboot_getValue( uint16 nFeature )
{
    return mboot_value( nFeature );
}

uint32 mboot_totalRam( )
{
    CHECK_IF_PRESENT( MULTIBOOT_MEMSIZE_PRESENT );

    return mboot_value( MULTIBOOT_MEM1_VALUE ) + mboot_value( MULTIBOOT_MEM2_VALUE );
}

uint32 mboot_bootDevice( )
{
    CHECK_IF_PRESENT( MULTIBOOT_BOOTDEV_PRESENT );

    return mboot_value( MULTIBOOT_BOOTDEV_VALUE );
}

char* mboot_cmdline( )
{
    CHECK_IF_PRESENT( MULTIBOOT_CMDLINE_PRESENT );

    return (char*)mboot_value( MULTIBOOT_CMDLINE_VALUE );
}

char* mboot_bootName( )
{
    CHECK_IF_PRESENT( MULTIBOOT_BOOTLOADER_NAME_PRESENT );

    return (char*)mboot_value( MULTIBOOT_BOOTLOADER_NAME_VALUE );
}

uint32 mboot_modsNum( )
{
    CHECK_IF_PRESENT( MULTIBOOT_MODS_PRESENT );

    return mboot_value( MULTIBOOT_MODS_NUM_VALUE );
}

uint32 mboot_modsPtr( )
{
    CHECK_IF_PRESENT( MULTIBOOT_MODS_PRESENT );

    return mboot_value( MULTIBOOT_MODS_ADDRESS_VALUE );
}

uint32 mboot_memmapLen( )
{
    CHECK_IF_PRESENT( MULTIBOOT_MMAP_PRESENT );

    return mboot_value( MULTIBOOT_MMAP_LENGTH_VALUE );
}

multiboot_memory_map_t*  mboot_memmap( )
{
    CHECK_IF_PRESENT( MULTIBOOT_MMAP_PRESENT );

    return (multiboot_memory_map_t*)( mboot_value( MULTIBOOT_MMAP_ADDRESS_VALUE ) + PAGING_KERNEL_OFFSET );
}

uint32 mboot_drivesLen( )
{
    CHECK_IF_PRESENT( MULTIBOOT_DRIVES_PRESENT );

    return mboot_value( MULTIBOOT_DRIVES_LENGTH_VALUE );
}

uint32 mboot_drivesPtr( )
{
    CHECK_IF_PRESENT( MULTIBOOT_DRIVES_PRESENT );

    return mboot_value( MULTIBOOT_DRIVES_ADDRESS_VALUE );
}

uint32 mboot_configTable( )
{
    CHECK_IF_PRESENT( MULTIBOOT_CONFIGTAB_PRESENT );

    return mboot_value( MULTIBOOT_CONFIGTAB_VALUE );
}

uint32 mboot_apmTable( )
{
    CHECK_IF_PRESENT( MULTIBOOT_APMTAB_PRESENT );

    return mboot_value( MULTIBOOT_APMTAB_VALUE );
}

multiboot_info_t* mboot_info( )
{
    return (multiboot_info_t*)( pMultibootHeader + PAGING_KERNEL_OFFSET );
}
