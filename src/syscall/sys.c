#include <base.h>
#include "sys.h"

#include <interrupt/interrupt.h>
#include <video/video.h>

void syscall_stub( );

void syscall_init( )
{
    idt_setAll( SYSCALL_INT, (uint32)(&syscall_stub), 0x8, 0x8E );
}

// we will be filling in these placeholder functions later

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void sys_exit( int32 nExit )
{
    return;
}

int32 sys_fork( )
{
    return -1;
}

int32 sys_kill( int32 nPID, int32 nSignal )
{
    return -1;
}

int32 sys_getpid( )
{
    return 1;
}

int32 sys_read( int32 nFd, char* pBuffer, int32 nLength )
{
    return 0;
}

int32 sys_write( int32 nFd, char* pBuffer, int32 nLength )
{
    if (nFd == 0)
    {
	screen_printString( pBuffer );
	return 0;
    }
    else
	return -1;
}

int32 sys_open( const char* szFilename, int32 nFlags, int32 nMode )
{
    return -1;
}

int32 sys_close( int32 nFd )
{
    return -1;
}

int32 sys_execve( char* szName, char** szArrArgv, char** szArrEnv )
{
    return -1;
}

int32 sys_fstat( int32 nFd, void* pStat )
{
    return 0;
}

int32 sys_stat( char* szFilename, void* pStat )
{
    return 0;
}

int32 sys_link( char* szFileOld, char* szFileNew )
{
    return -1;
}

int32 sys_unlink( char* szFilename )
{
    return -1;
}

int32 sys_lseek( int32 nFd, int32 nOffset, int32 nDirection )
{
    return 0;
}

int32 sys_sbrk( int32 nIncr )
{
    return 0;
}

int32 sys_times( void* pBuffer )
{
    return -1;
}

int32 sys_wait( int32* pStatus )
{
    return -1;
}

#pragma GCC diagnostic pop
