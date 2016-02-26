#ifndef SERIAL_H
#define SERIAL_H

/** @file serial.h
 * @brief Serial bus.
 * Self explanatory.
 */

void serial_init( );
void serial_writeChar( uint8 nSerial, uint8 nByte );
void serial_writeString( uint8 nSerial, const char* szString );
void serial_writeHex( uint8 nSerial, uint32 nHex );
uint8 serial_readChar( uint8 nSerial );

#endif
