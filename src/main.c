#include "video.h"
#include "gdt.h"
#include "interrupt.h"
#include "pit.h"
#include "panic.h"

int main( void *pMBHeader )
{
    gdt_init( );
    idt_init( );
    pit_init( 50 );
    
    screen_clear( );
    screen_setCursor( 0, 0 );
   
    screen_printString( "\nHello, World!" );
    screen_newline( );
    screen_scroll( );

    screen_printHex( 0xDEADBEEF );
    screen_newline( );
    screen_printDec( 1234567890 );

    panic("Panic Test.");

    return 0;
}
