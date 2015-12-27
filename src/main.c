#include "base.h"

#include <a20/a20.h>
#include <gdt/gdt.h>
#include <interrupt/interrupt.h>
#include <mem/kheap.h>
#include <mem/paging.h>

#include <video/video.h>
#include <pit/pit.h>
#include <rtc/rtc.h>
#include <serial/serial.h>
#include <multiboot/multiboot.h>
#include <ps2/ps2.h>
#include <initrd/initrd.h>
#include <syscall/sys.h>

/** Enter protected mode
 */
void k_pmode( )
{
    a20_enable( );
    gdt_init( );
    idt_init( );
    kheap_init( );
    paging_init( );
}

/** Kernel Main
 */
void kmain( )
{
    //Set up our environment for protected mode
    k_pmode( );

    //Enable lesser-important things
    pit_init( 50, (PIT_CHANNEL_0 | PIT_ACCESS_BOTH | PIT_MODE_2_2) );
    rtc_init( );
    serial_init( );
    ps2_init( );

    //Load ramdisk
    initrd_load( );

    //Demonstrate what we can do so far
    serial_writeString( 0, "Hello, World from serial!\n" );

    screen_clear( );
   
    screen_printString( "\nHello, World!" );
    screen_newline( );
    screen_scroll( );

    screen_printHex( 0xDEADBEEF );
    screen_newline( );
    screen_printDec( 1234567890 );

    screen_newline( );
    screen_newline( );

    screen_printDec( mboot_totalRam( ) );
    screen_printString(" kilobytes of ram\n");

    screen_printDec( mboot_modsNum( ) );
    screen_printString(" module(s)\nmodules address: ");
    screen_printHex( mboot_modsPtr( ) );

    screen_printString("\nmemmap size: ");
    screen_printDec( mboot_memmapLen( ) );
    screen_printString("\nmemmap address: ");
    screen_printHex( (unsigned int)mboot_memmapPtr( ) );

    screen_printString("\ndrivemap size: ");
    screen_printDec( mboot_drivesLen( ) );
    screen_printString("\ndrivemap address: ");
    screen_printHex( (unsigned int)mboot_drivesPtr( ) );

    screen_newline( );
    screen_newline( );
    screen_printString( "Contents of ramdisk: \n" );
    
    for (uint32 i=0;i < initrd_getNumFiles( );i++)
    {
	screen_printString( initrd_getFileName( i ) );
	screen_printChar( ':' );
	screen_printChar( ' ' );
	screen_printString( initrd_getData( i ) );
	screen_newline( );
    }

    while ( !rtc_hasTime( ) );
    
    screen_printString( "The current time is: " );
    screen_printDec( rtc_getHour( ) );
    screen_printChar( ':' );
    
    if ( rtc_getMinute( ) < 10 )
	screen_printChar( '0' );

    screen_printDec( rtc_getMinute( ) );
    screen_printChar( ' ' );

    screen_printDec( rtc_getMonth( ) );
    screen_printChar( '/' );
    screen_printDec( rtc_getDay( ) );
    screen_printChar( '/' );
    screen_printDec( rtc_getYear( ) );

    syscall_test( SYS_WRITE, 0, (uint32)"\nHello, syscall!", 16 );
}
