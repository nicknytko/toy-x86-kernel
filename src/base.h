#ifndef BASE_H
#define BASE_H

#include <stdint.h>

typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;

typedef uint8_t bool;

#define true 1
#define false 0

uint8 inb( uint16 port );
uint16 inw( uint16 port );
void outb( uint8 value, uint16 port );

#endif
