#include <base.h>
#include "pic.h"

void pic_sendEOI( uint32 nInterrupt )
{
    if ( nInterrupt >= 0x28 )
    {
	// send an EOI to slave pic if it's involved

	outb( PIC2_COM, PIC_EOI );
    }

    // always send an EOI to master

    outb( PIC1_COM, PIC_EOI );
}

void pic_IMRDisableAll( )
{
    // an IMR of 0xFF (all bits set) means that no IRQ can be called
    
    outb( PIC1_DATA, 0xFF );
    outb( PIC2_DATA, 0xFF );
}

void pic_setIMRMask( uint32 nIRQ )
{
    uint8 nIMR;

    // check if mask belongs to master of slave pic
    
    if ( nIRQ >= 8 )
    {
	// get original mask
	
	nIMR = inb( PIC2_DATA );

	// set bit for IRQ

	nIMR = nIMR | ( 1 << ( nIRQ - 8 ) );

	// send back to pic

	outb( PIC2_DATA, nIMR );
    }
    else
    {
	// do same for master

	nIMR = inb( PIC1_DATA );
	nIMR = nIMR | ( 1 << nIRQ );
	
	outb( PIC1_DATA, nIMR );
    }
}

void pic_clearIMRMask( uint32 nIRQ )
{
    uint8 nIMR;

    if ( nIRQ >= 8 )
    {
	nIMR = inb( PIC2_DATA );
	nIMR = nIMR & ~( 1 << ( nIRQ - 8 ) );

	outb( PIC2_DATA, nIMR );

	// make sure IRQ is cleared so that cascaded interrupts can be called
	
	pic_clearIMRMask( 0x2 );
    }
    else
    {
	nIMR = inb( PIC1_DATA );
	nIMR = nIMR & ~( 1 << nIRQ );
	
	outb( PIC1_DATA, nIMR );
    }
}

void pic_remap( )
{
    uint8 nMask1, nMask2;

    // save pic masks
    
    nMask1 = inb( PIC1_DATA );
    nMask2 = inb( PIC2_DATA );

    // start pic initialization

    outb( PIC1_COM, 0x11 );
    outb( PIC2_COM, 0x11 );

    // remap pic1 to interrupt 32 (0x20)

    outb( PIC1_DATA, 0x20 );

    // remap pic2 to interrupt 40 (0x28)

    outb( PIC2_DATA, 0x28 );

    // tell master pic that slave pic is at IRQ 2 (bit 2)

    outb( PIC1_DATA, 0x4 );

    // tell slave pic its cascade identity

    outb( PIC2_DATA, 0x2 );

    // set pics to 8086/8088 mode

    outb( PIC1_DATA, 0x1 );
    outb( PIC2_DATA, 0x1 );

    // restore our saved masks

    outb( PIC1_DATA, nMask1 );
    outb( PIC2_DATA, nMask2 );
}
