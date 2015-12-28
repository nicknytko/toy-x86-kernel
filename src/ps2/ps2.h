#ifndef PS2_H
#define PS2_H

/** @file ps2.h
 * @brief PS2 Keyboard driver
 */

//PS2 Controller Ports

#define PS2_DATA	0x60
#define PS2_COMMAND	0x64
#define PS2_STATUS	0x64

//PS2 Response Bytes

#define PS2_ACK			0xFA
#define PS2_TEST_SUCCESS	0x55

//PS2 Command Bytes

#define PS2_COM_DISABLE_AUX	0xA7
#define PS2_COM_ENABLE_AUX	0xA8

#define PS2_COM_DISABLE		0xAD
#define PS2_COM_ENABLE		0xAE

#define PS2_COM_READ_COMMAND	0x20
#define PS2_COM_WRITE_COMMAND	0x60

#define PS2_COM_READ_OUTPUT	0xD0
#define PS2_COM_WRITE_OUTPUT	0xD1
#define PS2_COM2_WRITE_OUTPUT	0xD4

#define PS2_COM_SELFTEST	0xAA

//PS2 Functions

/** Initializes the PS2 controller.
 */
void ps2_init( );

/** Checks if any auxiliary devices are available in the PS2 controller.
 * @return 1 if available, 0 if not
 */
bool ps2_auxAvailable( );

//PS2 Poll Functions

/** Blocks until the PS2 controller is ready to be read from.
 */
void ps2_wait_read( );

/** Blocks until the PS2 controller is ready to be written to.
 */
void ps2_wait_write( );

#endif
