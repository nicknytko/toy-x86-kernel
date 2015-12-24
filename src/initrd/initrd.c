#include <base.h>
#include "initrd.h"

#include <multiboot/multiboot.h>

#define INITRD_FILEHEADER_SIZE 		0x20C

static uint32 nInitrdAddress;
static uint32 nHeadersOffset;

bool initrd_load( )
{
    nInitrdAddress = get_dword( mboot_modsPtr( ) );

    if ( get_dword( nInitrdAddress ) == 0xDEADBEEF )
    {
	nHeadersOffset = nInitrdAddress + 8;
	return true;
    }

    nInitrdAddress = 0;
    return false;
}

uint32 initrd_getNumFiles( )
{
    if ( nInitrdAddress == 0 )
	return 0;

    return get_dword( nInitrdAddress + 4 );
}

char* initrd_getFileName( uint32 nFileNumber )
{
    if ( nHeadersOffset == 0 )
	return 0;

    if ( nFileNumber >= initrd_getNumFiles( ) )
	return 0;

    return (char*)(nHeadersOffset + nFileNumber * INITRD_FILEHEADER_SIZE);
}

static uint32 initrd_getFileOffset( uint32 nFileNumber )
{
    return get_dword( nHeadersOffset + 0x200 + nFileNumber * INITRD_FILEHEADER_SIZE );
}

uint32 initrd_getFileSize( uint32 nFileNumber )
{
    if ( nHeadersOffset == 0 )
	return 0;

    if ( nFileNumber >= initrd_getNumFiles( ) )
	return 0;

    return get_dword( nHeadersOffset + 0x204 + nFileNumber * INITRD_FILEHEADER_SIZE );
}

char* initrd_getData( uint32 nFileNumber )
{
    if ( nHeadersOffset == 0 )
	return 0;

    if ( nFileNumber >= initrd_getNumFiles( ) )
	return 0;

    return (char*)(nInitrdAddress + initrd_getFileOffset( nFileNumber ) );
}
