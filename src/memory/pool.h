#ifndef POOL_H
#define POOL_H

/*
 * @file pool.h
 * Simple allocator for internal kernel use
 */

#define POOL_UNUSED             0x0
#define POOL_USED               0x1
#define POOL_MINIMUM            0x10

typedef struct s_poolEntry
{
    struct  s_poolEntry* pNext;
    uint32 nLength;
    uint8 nFlags;
} __attribute__((__packed__)) s_poolEntry;

typedef struct __attribute__((__packed__))
{
    uint32 nStart, nEnd;
    s_poolEntry* pFirst;
} s_poolHeader;

/*
 * Initializes a memory pool and returns a pointer to the header
 */

s_poolHeader* pool_init( uint32 nAddress, uint32 nEnd );

/*
 * Allocates some memory
 */

void* pool_malloc( s_poolHeader* pHeader, uint32 nSize );

/*
 * Allocates aligned memory
 */

void* pool_malloca( s_poolHeader* pHeader, uint32 nSize, uint32 nAlignment );

/*
 * Frees a block of memry
 */

void pool_free( s_poolHeader* pHeader, void* pMemory );

/*
 * Prints the contents of the pool to serial 0
 */

void pool_debugPrint( s_poolHeader* pHeader );

#endif
