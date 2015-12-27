#include "base.h"
#include "pit.h"

#include <interrupt/interrupt.h>

#define PIT_PORT_CH0 		0x40
#define PIT_PORT_CH1 		0x41
#define PIT_PORT_CH2 		0x42
#define PIT_MODE     		0x43

#define PIT_INPUT_CLOCK 	1193180

static uint32 nPitTicks;

IRQ_HANDLER_NOARGS( pit_irq )
{
    nPitTicks++;
}

uint32 pit_getTicks( )
{
    return nPitTicks;
}

void pit_init( uint32 nFrequency, uint8 nFlags )
{
    //the pit calls irq 0, load our callback function
    irq_loadHandler( 0, (uint32) &pit_irq );

    //load the pit with our flags
    outb( PIT_MODE, nFlags );

    //the pit expects a frequency as a divisor of its clock
    nFrequency = PIT_INPUT_CLOCK / nFrequency;

    //send low and high bytes to pit
    outb( PIT_PORT_CH0, (nFrequency & 0xFF) );
    outb( PIT_PORT_CH0, ((nFrequency & 0xFF00) >> 8) );
}
