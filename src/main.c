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

    screen_printString( "hello\t" );
    screen_printString( "world\n" );

    return 0xDEADBABA;
}
