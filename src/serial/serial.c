#include <base.h>
#include "serial.h"

#include <bda/bda.h>
#include <interrupt/interrupt.h>

IRQ_HANDLER_NOARGS( serial_irq )
{
}

static uint16 serial_getPort( uint8 nSerial )
{
    switch( nSerial )
    {
    default:
    case 0:
	return bda_serial1Port( );
    case 1:
	return bda_serial2Port( );
    case 2:
	return bda_serial3Port( );
    case 3:
	return bda_serial4Port( );
    }
}

static void serial_initIndividual( uint16 nPort )
{
    //disable interrupts
    
    outb( nPort, 0x0 );

    //enable DLAB

    outb( nPort + 3, 0x80 );

    //set divisor to 3 (38400 baud)

    outb( nPort, 0x3 );
    outb( nPort + 1, 0x0 );

    //8 bits, no parity, one stop

    outb( nPort + 3, 0x03 );

    //enable FIFO

    outb( nPort + 2, 0xC7 );

    //enable IRQS

    outb( nPort + 4, 0x0B );
}

void serial_init( )
{
    switch( bda_numSerialPorts( ) )
    {
    case 4:
	serial_initIndividual( bda_serial4Port( ) );
	serial_writeString( 3, "Initialized serial port 4.\n" );
    case 3:
	serial_initIndividual( bda_serial3Port( ) );
	serial_writeString( 2, "Initialized serial port 3.\n" );
    case 2:
	serial_initIndividual( bda_serial2Port( ) );
	serial_writeString( 1, "Initialized serial port 2.\n" );
    case 1:
	serial_initIndividual( bda_serial1Port( ) );
	serial_writeString( 0, "Initialized serial port 1.\n" );
    case 0:
    default:
	break;
    }

    irq_loadHandler( (uint32)serial_irq, 4 );
}

void serial_writeChar( uint8 nSerial, uint8 nByte )
{
    uint16 nPort = serial_getPort( nSerial );
    uint8 nStatus = 0;

    while ( (nStatus & 0x20) != 0 )
    {
	nStatus = inb( nPort + 5 );
    }

    outb( nPort, nByte );
}

void serial_writeString( uint8 nSerial, const char* szString )
{
    while (*szString != 0)
    {
	serial_writeChar( nSerial, *szString );
	szString++;
    }
}

uint8 serial_readChar( uint8 nSerial )
{
    uint16 nPort = serial_getPort( nSerial );
    uint8 nInput = 0;

    while ( nInput == 0 )
    {
	nInput = inb( nPort + 5 );
    }

    return nInput;
}
