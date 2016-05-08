#ifndef BASE_H
#define BASE_H

#include <stdint.h>

/** @brief Basic functions and data types
 */

// Sized types

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;

/** Contents of the stack when pushad is called
 */

typedef struct
{
    int32 EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX, Unused;
} pushad_t;

// Boolean datatype

typedef uint8_t bool;

#define true 1
#define false 0

// Halt and wait for interrupts

void halt( );

// Port access

uint8 inb( uint16 port );
uint16 inw( uint16 port );
void outb( uint16 port, uint8 value );

// Memory

#define NULL 0

void set_dword( uint32 nAddress, uint32 nValue );
void set_word( uint32 nAddress, uint16 nValue );
void set_byte( uint32 nAddress, uint8 nValue );

uint32 get_dword( uint32 nAddress );
uint16 get_word( uint32 nAddress );
uint8 get_byte( uint32 nAddress );

// Word to byte conversion

#define word_lbyte( x ) (x & 0xFF)
#define word_hbyte( x ) ((x & 0xFF00) >> 8)

// Dword to word conversion

#define dword_lword( x ) (x & 0xFFFF)
#define dword_hword( x ) ((x & 0xFFFF0000) >> 16)

#endif
