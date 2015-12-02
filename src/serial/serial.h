#ifndef SERIAL_H
#define SERIAL_H

void serial_init( );
void serial_writeByte( unsigned char );
void serial_writeString( const char* );
unsigned char serial_readByte( );

#endif
