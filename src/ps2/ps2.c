#include <base.h>
#include "ps2.h"

#include <panic/panic.h>
#include <interrupt/interrupt.h>

static bool bPS2AuxAvailable;

void ps2_kb_poll( );

void ps2_wait_read( )
{
    while ( ( inb( PS2_STATUS ) & 0x1 ) == 0 );
}

void ps2_wait_write( )
{
    while ( ( inb( PS2_STATUS ) & 0x2 ) != 0 );
}

IRQ_HANDLER_NOARGS( ps2_irq )
{
    ps2_kb_poll( );
}

void ps2_init( )
{
    uint8 nCommand;
    
    //Disable auxilliary devices
    
    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_DISABLE_AUX );

    //Disable keyboard

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_DISABLE );

    //Get current keyboard command byte

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_READ_COMMAND );

    ps2_wait_read( );
    nCommand = inb( PS2_DATA );

    //Check if auxiliary devices are available
    
    if (nCommand & 0x10)
	bPS2AuxAvailable = true;

    //Start keyboard self-test

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_SELFTEST );

    ps2_wait_read( );
    
    if ( inb( PS2_DATA ) != PS2_TEST_SUCCESS )
	kpanic( "Failed PS/2 Self Test." );

    //Play around with the command byte
    
    nCommand |= 0x1; //Enable interrupts
    
    if (nCommand & 0x40)
	nCommand ^= 0x40; //Disable scancode translation

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_WRITE_COMMAND );
    
    ps2_wait_write( );
    outb( PS2_DATA, nCommand ); //Upload byte back to ps2

    //Load the IRQ Handler

    irq_loadHandler( 1, (uint32) &ps2_irq );

    //Re-enable auxiliary devices (if available)
    
    if ( ps2_auxAvailable( ) )
    {
	ps2_wait_write( );
	outb( PS2_COMMAND, PS2_COM_ENABLE_AUX );
    }
    
    //Re-enable the keyboard

    ps2_wait_write( );
    outb( PS2_COMMAND, PS2_COM_ENABLE );
}

bool ps2_auxAvailable( )
{
    return bPS2AuxAvailable;
}
