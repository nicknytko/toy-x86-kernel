#ifndef MULTIBOOT_H
#define MULTIBOOT_H

unsigned int mboot_totalRam( ); //in kilobytes
unsigned int mboot_bootDevice( );
unsigned int mboot_cmdline( );

char*        mboot_bootName( );

unsigned int mboot_modsNum( );
unsigned int*mboot_modsPtr( );

unsigned int mboot_memmapLen( );
void*        mboot_memmapPtr( );

unsigned int mboot_drivesLen( );
void*        mboot_drivesPtr( );

void*        mboot_configTable( );
void*        mboot_apmTable( );

#endif
