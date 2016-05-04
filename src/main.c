#include "base.h"

#include <a20/a20.h>
#include <gdt/gdt.h>
#include <interrupt/interrupt.h>
#include <memory/heap.h>
#include <memory/paging.h>

#include <video/video.h>
#include <pit/pit.h>
#include <rtc/rtc.h>
#include <serial/serial.h>
#include <multiboot/multiboot.h>
#include <ps2/ps2.h>
#include <fs/initrd/initrd.h>
#include <syscall/sys.h>
#include <info/cpuid.h>

#include <panic/panic.h>

/** Demonstrate what we are capable of doing so far
 */

void kdemo( )
{
    // Test out serial
    
    serial_writeString( 0, "Hello, World from serial!\n" );

    // Test out our screen printing functions
    
    screen_clear( );
    
    screen_printString( "\nHello, World!" );
    screen_newline( );
    screen_scroll( );

    screen_printHex( 0xDEADBEEF );
    screen_newline( );
    screen_printDec( 1234567890 );

    screen_newline( );
    screen_newline( );

    // Miscellaneous multiboot data
    
    screen_printDec( mboot_totalRam( ) );
    screen_printString(" kilobytes of ram\n");
    
    screen_printDec( mboot_modsNum( ) );
    screen_printString(" module(s)\nmodules address: ");
    screen_printHex( mboot_modsPtr( ) );

    // Print out a memory map to serial 0

    {
        multiboot_memory_map_t* memmap = mboot_memmap( );
    
        for ( uint32 i=0; i < mboot_memmapLen( ) / sizeof( multiboot_memory_map_t ); i++ )
        {
            serial_writeString( 0, "memory map entry at ");
            serial_writeHex( 0, memmap[i].addr );
            serial_writeString( 0, ", size " );
            serial_writeHex( 0, memmap[i].len );
            serial_writeString( 0, ", " );

            switch ( memmap[i].type )
            {
            case MULTIBOOT_MEMORY_AVAILABLE:
                serial_writeString( 0, "available" );
                break;
            case MULTIBOOT_MEMORY_RESERVED:
                serial_writeString( 0, "reserved" );
                break;
            case MULTIBOOT_MEMORY_ACPI_RECLAIMABLE:
                serial_writeString( 0, "acpi reclaimable" );
                break;
            case MULTIBOOT_MEMORY_NVS:
                serial_writeString( 0, "nvs" );
                break;
            case MULTIBOOT_MEMORY_BADRAM:
                serial_writeString( 0, "bad" );
                break;
            default:
                serial_writeString( 0, "unknown" );
            }

            serial_writeChar( 0, '\n' );
        }
    }

    // Ramdisk
    
    screen_newline( );
    screen_newline( );
    screen_printString( "Contents of ramdisk: \n" );
    
    for (uint32 i=0;i < initrd_getNumFiles( );i++)
    {
        screen_printString( initrd_getFileName( i ) );
        screen_printChar( ':' );
        screen_printChar( ' ' );
        screen_printString( initrd_getData( i ) );
        screen_newline( );
    }

    // Real time clock
    
    while ( !rtc_hasTime( ) );
    
    screen_printString( "The current time is: " );
    screen_printDec( rtc_getHour( ) );
    screen_printChar( ':' );
    
    if ( rtc_getMinute( ) < 10 )
        screen_printChar( '0' );

    screen_printDec( rtc_getMinute( ) );
    screen_printChar( ' ' );

    screen_printDec( rtc_getMonth( ) );
    screen_printChar( '/' );
    screen_printDec( rtc_getDay( ) );
    screen_printChar( '/' );
    screen_printDec( rtc_getYear( ) );

    // Example syscall (not very impressive)
    
    syscall_test( SYS_WRITE, 0, (uint32)"\nHello, syscall!\n", 16 );

    // CPU Vendor
    
    screen_printString( cpuid_getVendor( ) );

    // Test out our memory allocation
    
    {
        serial_writeString( 0, "Memory allocation test!\n" );
        
        void* pBuffer1, *pBuffer2, *pBuffer3;

        pBuffer1 = kmalloc(64);
        pBuffer2 = kmalloc(64);

        serial_writeHex( 0, (uint32) pBuffer1 );
        serial_writeChar( 0, '\n' );
        serial_writeHex( 0, (uint32) pBuffer2 );
        serial_writeChar( 0, '\n' );
        
        kfree( pBuffer1 );

        pBuffer1 = kmalloc(32);
        pBuffer3 = kmalloc(16);

        serial_writeHex( 0, (uint32) pBuffer1 );
        serial_writeChar( 0, '\n' );
        serial_writeHex( 0, (uint32) pBuffer3 );
        serial_writeChar( 0, '\n' );

        kfree( pBuffer1 );
        kfree( pBuffer2 );
        kfree( pBuffer3 );

        pBuffer1 = kmalloc( 128 );

        serial_writeHex( 0, (uint32) pBuffer1 );
        serial_writeChar( 0, '\n' );

        kfree( pBuffer1 );
    }
}

/** Initialize kernel for higher half
 */
void kinit( )
{
    paging_init( );
    paging_initHigherHalf( PAGING_KERNEL_OFFSET );
}

void kmain( )
{
    // Set up our protected mode junk
    
    a20_enable( );
    gdt_init( );
    idt_init( );
    kheap_init( );
    syscall_init( );
    
    // Load our less important devices

    pit_init( 50, (PIT_CHANNEL_0 | PIT_ACCESS_BOTH | PIT_MODE_2_2) );
    rtc_init( );
    serial_init( );
    ps2_init( );
    initrd_load( );    
    
    // Run our demo
    
    kdemo( );

    // End

    halt( );
}
