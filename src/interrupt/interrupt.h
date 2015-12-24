#ifndef INTERRUPT_H
#define INTERRUPT_H

/** @brief Various values available to an irq handler.
 * Represents the stack pushed by the hardware when an IRQ is called.
 */
typedef struct s_irqStack
{
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax; //pushed by irq handler
    /** @brief Interrupt number.  For an IRQ, this is 32 + the IRQ number. */
    uint32 nInterrupt;
    /** @brief Error code.  For an IRQ, this is always 0. */
    uint32 nError;
    uint32 eip, cs, eflags, user_esp, ss, es, ds, fs, gs; //pushed automatically by interrupt
} s_irqStack;

#define IRQ_HANDLER( name ) void name ( s_irqStack* pStack )
#define IRQ_HANDLER_NOARGS( name ) void name ()

/** Initializes the interrupt table
 */
void idt_init( );

/** Sets a handler for an IRQ
 * @param pHandler Pointer to a function to be called for the IRQ
 * @param nIRQ Number of IRQ
 */
void irq_loadHandler( uint32 pHandler, uint32 nIRQ );

/** @brief Disable interrupts
 * Calls CLI and disables NMI's.
 */
void int_cli( );

/** @brief Enable interrupts
 * Calls STI and enables NMI's.
 */
void int_sti( );

/** Enables NMI's
 */
void nmi_enable( );

/** Disables NMI's
 */
void nmi_disable( );

#endif
