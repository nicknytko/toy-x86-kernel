#include "video.h"
#include "gdt.h"
#include "interrupt.h"
#include "pit.h"

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

    return 0xDEADBABA;
}
