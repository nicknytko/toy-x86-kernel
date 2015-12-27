#include <base.h>
#include "interrupt.h"
#include "pic.h"

extern uint32 IDT_TABLE[];
extern uint32 IRQ_TABLE[];

void idt_setAll( uint32 nIndex, uint32 pISR, uint16 nSelector, uint8 nFlags )
{
    uint32 pEntry = (uint32)(&IDT_TABLE[nIndex * 2]);
    
    set_word( pEntry, dword_lword( pISR ) );
    set_word( pEntry + 2, nSelector );
    set_byte( pEntry + 4, 0 );
    set_byte( pEntry + 5, nFlags );
    set_word( pEntry + 6, dword_hword( pISR ) );
}

void idt_set( uint32 nIndex, uint32 pISR )
{
    idt_setAll( nIndex, pISR, 0x08, 0x8E );
}

void irq_loadHandler( uint32 nIRQ, uint32 pHandler )
{
    if (nIRQ > 16)
	return;

    IRQ_TABLE[ nIRQ ] = pHandler;

    pic_clearIMRMask( nIRQ );
}
