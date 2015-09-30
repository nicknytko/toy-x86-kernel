#include "video.h"
#include "gdt.h"
#include "interrupt.h"
#include "pit.h"
#include "panic.h"
#include "serial.h"
#include "a20.h"

int main( void *pMBHeader )
{
    a20_enable( );

    gdt_init( );
    idt_init( );
    pit_init( 50 );
    serial_init( );
   
    serial_writeString( "Hello, World from serial!\n" );

    screen_clear( );
    screen_setCursor( 0, 0 );
   
    screen_printString( "\nHello, World!" );
    screen_newline( );
    screen_scroll( );

    screen_printHex( 0xDEADBEEF );
    screen_newline( );
    screen_printDec( 1234567890 );

    return 0;
}
