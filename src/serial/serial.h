#ifndef SERIAL_H
#define SERIAL_H

/** @file serial.h
 * @brief Serial bus.
 * Self explanatory.
 */

#define SERIAL_BDA_COM		0x400
#define SERIAL_COM1_PORT	0x3F8

void serial_init( );
void serial_writeChar( uint8 nSerial, uint8 nByte );
void serial_writeString( uint8 nSerial, const char* szString );
uint8 serial_readChar( uint8 nSerial );

#endif
