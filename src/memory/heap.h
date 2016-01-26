#ifndef KHEAP_H
#define KHEAP_H

/** Creates a very simple "dumb" allocator
 */
void kheap_init( );

/** Allocates a block of memory
 * @param size Size in bytes
 * @returns Pointer to the memory
 */
unsigned int kmalloc( unsigned int size );

/** Allocates a page-aligned block of memory
 * @param size Size in bytes
 * @returns Pointer to the memory
 */
unsigned int kmalloc_a( unsigned int size );

#endif
