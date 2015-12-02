#ifndef PIT_H
#define PIT_H

// PIT Specific Values
// Channel Select

#define PIT_CHANNEL_0 		0x0
#define PIT_CHANNEL_1 		0x80
#define PIT_CHANNEL_2 		0x40
#define PIT_CHANNEL_3 		0xC0

// Channel Mode

#define PIT_LATCH_COUNT 	0x0
#define PIT_ACCESS_LOW 		0x20
#define PIT_ACCESS_HIGH 	0x10
#define PIT_ACCESS_BOTH 	0x30

// Operating Mode

#define PIT_MODE_0 		0x0
#define PIT_MODE_1 		0x8
#define PIT_MODE_2 		0x4
#define PIT_MODE_3 		0xC
#define PIT_MODE_4 		0x2
#define PIT_MODE_5 		0xA
#define PIT_MODE_2_2		0x6
#define PIT_MODE_3_2		0xE

void pit_init( uint32 frequency, uint8 nFlags );
uint32 pit_getTicks( );

#endif
