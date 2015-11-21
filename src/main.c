#include "video.h"
#include "gdt.h"
#include "interrupt.h"
#include "pit.h"
#include "panic.h"
#include "serial.h"
#include "a20.h"
#include "kheap.h"
#include "paging.h"
#include "multiboot.h"
#include "keyboard.h"

/** Kernel Main
 */
void main( )
{
    a20_enable( );

    gdt_init( );
    idt_init( );
    pit_init( 50 );
    serial_init( );
    kb_init( );
    kheap_init( );
    paging_init( );

    serial_writeString( "Hello, World from serial!\n" );

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
    screen_printHex( mboot_modsPtr( )[0] );

    screen_printString("\nmemmap size: ");
    screen_printDec( mboot_memmapLen( ) );
    screen_printString("\nmemmap address: ");
    screen_printHex( (unsigned int)mboot_memmapPtr( ) );

    mboot_drivesLen( );
    mboot_drivesPtr( );
   
    screen_printString("\ndrivemap size: ");
    screen_printDec( mboot_drivesLen( ) );
    screen_printString("\ndrivemap address: ");
    screen_printHex( (unsigned int)mboot_drivesPtr( ) );
}
