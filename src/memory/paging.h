#ifndef PAGING_H
#define PAGING_H

#define PAGING_KERNEL_OFFSET		0xC0000000
#define PAGING_ADDRESS_TO_ENTRY(x)	(x / 0x400000)

#define PAGE_PRESENT            	0x1
#define PAGE_EMPTY			0x0
#define PAGE_WRITABLE           	0x2
#define PAGE_READONLY			0x0
#define PAGE_USERMODE           	0x4
#define PAGE_KERNELMODE			0x0
#define PAGE_WRITETHROUGH       	0x8
#define PAGE_CACHEDISABLED      	0x10
#define PAGE_ACCESSED           	0x20
#define PAGE_DIRTY              	0x40
#define PAGE_TABLE_4MBPAGES     	0x80
#define PAGE_GLOBAL             	0x100

/** Set a table in the paging directory
 */

void paging_setTable( uint32 nIndex, uint32 pAddress, uint8 nFlags );

/** Remove a table in the paging directory
 */

void paging_removeTable( uint32 nIndex );

/** Copies a table pointer into another directory entry
 */

void paging_cloneTable( uint32 nOld, uint32 nNew );

/** Initialize paging by identity mapping the first 4mb
 */
void paging_init( );

/** Jumps to the kernel offset and disables the 4mb identity mapping
 */
void paging_initHigherHalf( uint32 nOffset );

#endif
