#include <base.h>
#include "a20.h"

#include <ps2/ps2.h>

//defined in a20_bios.s
uint16 a20_enable_bios( );
void a20_enable_fast( );

bool ps2_exists( )
{
    return true;
}

void a20_enable_ps2( )
{
    uint8 nConfig;
    
    // disable ps2 controller
    
    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_DISABLE );

    // read from the controller output port

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_READ_OUTPUT );

    ps2_wait_read( );
    nConfig = inb( PS2_DATA );
    nConfig |= 0x2; //enable a20 gate by setting second bit

    // write back to the controller output port

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_WRITE_OUTPUT );

    ps2_wait_write( );
    outb( PS2_DATA, nConfig );

    // re-enable ps2 controller

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_ENABLE );
}

void a20_enable( )
{
    if (a20_enable_bios( ))
	return;

    if (ps2_exists( ))
    {
	a20_enable_ps2( );
	return;
    }

    a20_enable_fast( );
}
