#ifndef MULTIBOOT_H
#define MULTIBOOT_H

/**
 * @file multiboot.h
 * @brief Multiboot interface
 *
 * Interface for accessing information passed by the multiboot-compatible bootloader
 */

/** Gets the total amount of ram available
 * @returns Size of RAM in kilobytes
 */
unsigned int mboot_totalRam( );

/** Checks if a boot device is set
 * @returns 1 if true, 0 if not
 */
unsigned int mboot_bootDevice( );

/** Returns a pointer to any command-line arguments passed through bootloader
 * @returns Pointer to null-terminated string if available, NULL if not
 */
char* mboot_cmdline( );

/** Returns the name of the bootloader
 * @returns Pointer to null-terminated string if available, NULL if not
 */
char* mboot_bootName( );

/** Returns the number of multiboot modules
 * @returns Number of modules
 */
unsigned int mboot_modsNum( );

/** Returns a pointer to the first multiboot module
 * @returns first module
 */
unsigned int* mboot_modsPtr( );

/** Returns the length of the multiboot memory map
 * @returns Size in bytes
 */
unsigned int mboot_memmapLen( );

/** Returns a pointer to the memory map
 * @returns Pointer to memory map
 */
void*        mboot_memmapPtr( );

/** Returns the number of detected drives
 * @returns Number of drives
 */
unsigned int mboot_drivesLen( );

/** Returns a pointer to multiboot drive information
 * @returns Drive information
 */
void*        mboot_drivesPtr( );

/** Returns a pointer to the ROM configuration table
 * @returns ROM Table, if available
 */
void*        mboot_configTable( );

/** Returns a pointer fo the APM table
 * @returns APM Table, if available
 */
void*        mboot_apmTable( );

#endif
