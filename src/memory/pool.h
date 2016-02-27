#ifndef POOL_H
#define POOL_H

/** @file pool.h
 * @brief Simple allocator for internal kernel use
 */

#define POOL_UNUSED             0x0
#define POOL_USED               0x1
#define POOL_MINIMUM            0x10

/** @brief Pool Entry
 * Header that immediately precedes every block of allocated memory
 */

typedef struct s_poolEntry
{
    struct  s_poolEntry* pNext;
    uint32 nLength;
    uint8 nFlags;
} __attribute__((__packed__)) s_poolEntry;

/** @brief Pool Header
 * The beginning of the pool.
 */

typedef struct __attribute__((__packed__))
{
    uint32 nStart, nEnd;
    s_poolEntry* pFirst;
} s_poolHeader;

/** Initializes a memory pool and returns a pointer to the header
 */

s_poolHeader* pool_init( uint32 nAddress, uint32 nEnd );

/** Allocates memory from the pool
 * @param pHeader Pool header structure
 * @param nSize Size in bytes to allocate
 * @returns Pointer to allocated memory
 */

void* pool_malloc( s_poolHeader* pHeader, uint32 nSize );

/** Allocates aligned memory from the pool
 * @param pHeader Pool header structure
 * @param nSize Size in bytes to allocate
 * @param nAlignment Alignment in bytes
 * @returns Pointer to allocated memory
 */

void* pool_malloca( s_poolHeader* pHeader, uint32 nSize, uint32 nAlignment );

/** Frees a block of allocated memory
 * @param pHeader Pool header structure
 * @param pMemory Allocated memory to free
 */

void pool_free( s_poolHeader* pHeader, void* pMemory );

/** Prints the contents of the pool to serial bus 0
 * @param pHeader Pool header structure
 */

void pool_debugPrint( s_poolHeader* pHeader );

#endif
