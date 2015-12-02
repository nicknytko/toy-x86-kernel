#ifndef INTERRUPT_H
#define INTERRUPT_H

/** Initializes the interrupt table
 */
void idt_init( );

/** Sets a bit in the IMR register
 * Used to disable a certain IRQ
 * @param nMask The number bit to set
 */
void pic_setIMRMask( unsigned int nMask );

/** Clears a bit in the IMR register
 * Used to enable a certain IRQ
 * @param nMask The number bit to set
 */
void pic_clearIMRMask( unsigned int nMask );

/** Sets a handler for an IRQ
 * @param pHandler Pointer to a function to be called for the IRQ
 * @param nIRQ Number of IRQ
 */
void irq_loadHandler( void* pHandler, int nIRQ );

#endif
