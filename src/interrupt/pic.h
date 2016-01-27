#ifndef PIC_H
#define PIC_H

/** @file pic.h
 * @brief 8259 PIC interface.
 */

#define PIC1_BASE               0x20
#define PIC2_BASE               0xA0
#define PIC1_COM                PIC1_BASE
#define PIC2_COM                PIC2_BASE
#define PIC1_DATA               (PIC1_BASE+1)
#define PIC2_DATA               (PIC2_BASE+1)

#define PIC_EOI                 0x20

/** Sets the IMR registers to 0xFF
 * Disables all IRQ's
 */
void pic_IMRDisableAll( );

/** Sets a bit in the IMR register
 * Used to disable a certain IRQ
 * @param nMask The number bit to set
 */
void pic_setIMRMask( uint32 nMask );

/** Clears a bit in the IMR register
 * Used to enable a certain IRQ
 * @param nMask The number bit to set
 */
void pic_clearIMRMask( uint32 nMask );

/** Remap the 8259 PIC chip
 */
void pic_remap( );

#endif
