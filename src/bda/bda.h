#ifndef BDA_H
#define BDA_H

/* Good documentation for the Bios Data Area can be found here
   http://www.bioscentral.com/misc/bda.htm */

#define BDA_BASE_ADDRESS		0x0400
#define BDA_SERIAL1_PORT		BDA_BASE_ADDRESS
#define BDA_SERIAL2_PORT		(BDA_BASE_ADDRESS + 0x2)
#define BDA_SERIAL3_PORT		(BDA_BASE_ADDRESS + 0x4)
#define BDA_SERIAL4_PORT		(BDA_BASE_ADDRESS + 0x6)
#define BDA_PARALLEL1_PORT		(BDA_BASE_ADDRESS + 0x8)
#define BDA_PARALLEL2_PORT		(BDA_BASE_ADDRESS + 0xA)
#define BDA_PARALLEL3_PORT		(BDA_BASE_ADDRESS + 0xC)
#define BDA_PARALLEL4_PORT		(BDA_BASE_ADDRESS + 0xE)
#define BDA_EQUIPMENT			(BDA_BASE_ADDRESS + 0x10)
#define BDA_MEMSIZE			(BDA_BASE_ADDRESS + 0x13)
#define BDA_KEYBOARD_FLAGS		(BDA_BASE_ADDRESS + 0x17)
#define BDA_KEYBOARD_FLAGS2		(BDA_BASE_ADDRESS + 0x18)

/** Gets the number of serial ports available (0-4)
 */
uint8 bda_numSerialPorts( );

/** Gets the number of parallel ports available (0-3)
 */
uint8 bda_numParallelPorts( );

/** Gets the port for serial port 1
 */
uint16 bda_serial1Port( );

/** Gets the port for serial port 2
 */
uint16 bda_serial2Port( );

/** Gets the port for serial port 3
 */
uint16 bda_serial3Port( );

/** Gets the port for serial port 4
 */
uint16 bda_serial4Port( );

/** Gets the port for parallel port 1
 */
uint16 bda_parallel1Port( );

/** Gets the port for parallel port 2
 */
uint16 bda_parallel2Port( );

/** Gets the port for parallel port 3
 */
uint16 bda_parallel3Port( );

#endif
