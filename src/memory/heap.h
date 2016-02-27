#ifndef KHEAP_H
#define KHEAP_H

/** @file heap.h
 * @brief Kernel malloc functions
 */

#define KHEAP_PHYSICAL_START	0x07E00
#define KHEAP_PHYSICAL_END	0x7FFFF

/** Sets up dynamic memory allocation for the kernel
 */
void kheap_init( );

/** Allocates a block of memory
 * @param nSize Size in bytes
 * @returns Pointer to the memory
 */
void* kmalloc( uint32 nSize );

/** Allocates an aligned block of memory
 * @param nSize Size in bytes
 * @param nAlignment Byte size to align to
 * @returns Pointer to the memory
 */
void* kmalloc_a( uint32 nSize, uint32 nAlignment );

/** Frees a block of memory
 * @param pBlock The block of memory to free
 */
void kfree( void* pBlock );

/** Prints a debug map of the kernel heap to serial 0
 */
void kheap_debugPrint( );

#endif
