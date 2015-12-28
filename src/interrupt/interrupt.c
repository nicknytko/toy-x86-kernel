#include <base.h>
#include "interrupt.h"
#include "pic.h"

#include <video/video.h>
#include <panic/panic.h>

extern uint32 IDT_TABLE[];
extern uint32 IRQ_TABLE[];

void isr_handler( uint8 nInterrupt, uint8 nError, uint32 nAddress )
{
    screen_printString( "Received interrupt " );
    screen_printDec( nInterrupt );
    screen_printString( " at address " );
    screen_printHex( nAddress );
    screen_newline( );

    switch (nInterrupt)
    {
    case 0:
	screen_printString( "Divide-by-zero" );
	break;
    case 1:
	screen_printString( "Debug interrupt" );
	break;
    case 2:
	screen_printString( "Non-maskable interrupt" );
	break;	
    case 3:
	screen_printString( "Breakpoint" );
	break;       
    case 4:
	screen_printString( "Overflow" );
	break;	
    case 5:
	screen_printString( "Bound Range Exceeded" );
	break;	
    case 6:
	screen_printString( "Invalid Opcode" );
	break;       
    case 7:
	screen_printString( "Device Not Available" );
	break;	
    case 8:
	kpanic( "Double Fault" );
	break;	
    case 9:
	screen_printString( "Coprocessor Segment Overrun" );
	break;	
    case 10:
	screen_printString( "Invalid TSS" );
	screen_printString( " (error code " );
	screen_printDec( nError );
	screen_printString( ")" );
	break;	
    case 11:
	screen_printString( "Segment Not Present" );
	screen_printString( " (error code " );
	screen_printDec( nError );
	screen_printString( ")" );
	break;	
    case 12:
	screen_printString( "Stack-Segment Fault" );
	screen_printString( " (error code " );
	screen_printDec( nError );
	screen_printString( ")" );	
	break;	
    case 13:
	screen_printString( "General Protection Fault" );
	screen_printString( " (error code " );
	screen_printDec( nError );
	screen_printString( ")" );	
	break;	
    case 14:
	screen_printString( "Page Fault" );
	screen_printString( " (error code " );
	screen_printDec( nError );
	screen_printString( ")" );	
	break;	
    case 16:
	screen_printString( "x87 Floating-Point Exception" );
	break;
    case 17:
	screen_printString( "Alignment Check" );
	screen_printString( " (error code " );
	screen_printDec( nError );
	screen_printString( ")" );	
	break;
    case 18:
	screen_printString( "Machine Check" );
	break;	
    case 19:
	screen_printString( "SIMD Floating-Point Exception" );
	break;	
    case 20:
	screen_printString( "Virtualization Exception" );
	break;
    default:
	screen_printString( "Unknown interrupt" );
	break;	
    }

    screen_newline( );
}

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
