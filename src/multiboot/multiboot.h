#ifndef MULTIBOOT_H
#define MULTIBOOT_H

/**
 * @file multiboot.h
 * @brief Multiboot interface
 *
 * Interface for accessing information passed by the multiboot-compatible bootloader
 */

/* Information on this can be found in the GRUB Documentation.
   https://www.gnu.org/software/grub/manual/multiboot/multiboot.html#Boot-information-format */

#define MULTIBOOT_MEMSIZE_PRESENT		0x1
#define MULTIBOOT_BOOTDEV_PRESENT		0x2
#define MULTIBOOT_CMDLINE_PRESENT		0x4
#define MULTIBOOT_MODS_PRESENT			0x8
#define MULTIBOOT_SYMS_PRESENT			0x10
#define MULTIBOOT_SYMS2_PRESENT			0x20
#define MULTIBOOT_MMAP_PRESENT			0x40
#define MULTIBOOT_DRIVES_PRESENT		0x80
#define MULTIBOOT_CONFIGTAB_PRESENT		0x100
#define MULTIBOOT_BOOTLOADER_NAME_PRESENT	0x200
#define MULTIBOOT_APMTAB_PRESENT		0x400
#define MULTIBOOT_VBE_PRESENT			0x800

#define MULTIBOOT_MEM1_VALUE			0x4
#define MULTIBOOT_MEM2_VALUE			0x8
#define MULTIBOOT_BOOTDEV_VALUE			0xC
#define MULTIBOOT_CMDLINE_VALUE			0x10
#define MULTIBOOT_MODS_NUM_VALUE		0x14
#define MULTIBOOT_MODS_ADDRESS_VALUE		0x18
#define MULTIBOOT_MMAP_LENGTH_VALUE		0x2C
#define MULTIBOOT_MMAP_ADDRESS_VALUE		0x30
#define MULTIBOOT_DRIVES_LENGTH_VALUE		0x34
#define MULTIBOOT_DRIVES_ADDRESS_VALUE		0x38
#define MULTIBOOT_CONFIGTAB_VALUE		0x3C
#define MULTIBOOT_BOOTLOADER_NAME_VALUE		0x40
#define MULTIBOOT_APMTAB_VALUE			0x44
#define MULTIBOOT_VBE_OFFSET			0x48

/** Checks if a particular feature is present in the multiboot info structure
 * @param nFeature MULTIBOOT_X_PRESENT
 * @returns True if the particular feature is present
 */
bool mboot_isPresent( uint16 nFeature );

/** Returns the value of a particular entry in the multiboot info structure
 * @param nFeature MULTIBOOT_X_VALUE
 * @returns Value
 */
uint32 mboot_getValue( uint16 nFeature );

/** Gets the total amount of ram available
 * @returns Size of RAM in kilobytes
 */
uint32 mboot_totalRam( );

/** Checks if a boot device is set
 * @returns 1 if true, 0 if not
 */
uint32 mboot_bootDevice( );

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
uint32 mboot_modsNum( );

/** Returns a pointer to the first multiboot module
 * @returns first module
 */
uint32 mboot_modsPtr( );

/** Returns the length of the multiboot memory map
 * @returns Size in bytes
 */
uint32 mboot_memmapLen( );

/** Returns a pointer to the memory map
 * @returns Pointer to memory map
 */
uint32 mboot_memmapPtr( );

/** Returns the number of detected drives
 * @returns Number of drives
 */
uint32 mboot_drivesLen( );

/** Returns a pointer to multiboot drive information
 * @returns Drive information
 */
uint32 mboot_drivesPtr( );

/** Returns a pointer to the ROM configuration table
 * @returns ROM Table, if available
 */
uint32 mboot_configTable( );

/** Returns a pointer fo the APM table
 * @returns APM Table, if available
 */
uint32 mboot_apmTable( );

#endif
