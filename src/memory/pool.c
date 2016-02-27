#include <base.h>
#include <serial/serial.h>

#include "pool.h"

/*
 * Align an address
 */

static inline uint32 pool_align( uint32 nAddress, uint32 nAlignment )
{
    if ( nAlignment == 0 )
        return nAddress;
    else
        return ( ( nAddress / nAlignment ) + 1 ) * nAlignment;
}

/*
 * Find the previous entry in the list
 */

static s_poolEntry* pool_findPrevious( s_poolHeader* pHeader, s_poolEntry* pEntry )
{
    if ( pHeader->pFirst == NULL )
        return NULL;

    s_poolEntry* pCurrent = pHeader->pFirst;

    while ( pCurrent->pNext != NULL )
    {
        if ( pCurrent->pNext == pEntry )
            return pCurrent;

        pCurrent = pCurrent->pNext;
    }

    return NULL;
}

/* 
 * Find unused pools next to each other and merge them
 */

static void pool_prune( s_poolHeader* pHeader )
{
    if ( pHeader->pFirst == NULL )
        return;

    s_poolEntry* pCurrent = pHeader->pFirst;
    s_poolEntry* pLast = NULL;
    bool bLastUnused = false;
    
    while ( pCurrent != NULL )
    {
        if ( bLastUnused && pCurrent->nFlags == POOL_UNUSED )
        {
            pLast->pNext = pCurrent->pNext;
            pLast->nLength += sizeof( s_poolHeader ) + pCurrent->nLength;
            pCurrent = pLast;
            
            bLastUnused = true;
        }
        else if ( pCurrent->nFlags == POOL_UNUSED )
        {
            bLastUnused = true;
            pLast = pCurrent;
        }
        else if ( pCurrent->nFlags == POOL_USED )
        {
            bLastUnused = false;
            pLast = pCurrent;
        }

        pCurrent = pCurrent->pNext;
    }
}

s_poolHeader* pool_init( uint32 nAddress, uint32 nEnd )
{
    // Create an empty header
    
    s_poolHeader* pHeader = (s_poolHeader*)pool_align( nAddress, sizeof( s_poolHeader ) );
    
    pHeader->nStart = nAddress;
    pHeader->nEnd = nEnd;
    pHeader->pFirst = NULL;

    return pHeader;
}

void* pool_malloc( s_poolHeader* pHeader, uint32 nSize )
{
    return pool_malloca( pHeader, nSize, 0 );
}

void* pool_malloca( s_poolHeader* pHeader, uint32 nSize, uint32 nAlignment )
{
    // If we have no memory allocated then create the first entry
    
    if ( pHeader->pFirst == NULL )
    {
        uint32 nAddress = (uint32)(pHeader) + sizeof( s_poolHeader );
        nAddress = pool_align( nAddress, nAlignment );
        
        s_poolEntry* pEntry = (s_poolEntry*)nAddress;
        pEntry->pNext = NULL;
        pEntry->nLength = nSize;
        pEntry->nFlags = POOL_USED;

        pHeader->pFirst = pEntry;

        return (s_poolEntry*)( (uint32)pEntry + sizeof( s_poolEntry ) );
    }
    else
    {
        // Search for an empty block

        bool bLooping = true;
        s_poolEntry* pEntry = pHeader->pFirst;

        while ( bLooping )
        {
            if ( pEntry->nFlags == POOL_UNUSED && pEntry->nLength >= nSize )
            {
                // If we do, mark it as used
                
                pEntry->nFlags = POOL_USED;

                // Check if we have empty space to make another entry

                if ( pEntry->pNext != NULL && pEntry->nLength - nSize >= POOL_MINIMUM )
                {
                    s_poolEntry* pNext = (s_poolEntry*)( (uint32)pEntry + nSize + sizeof( s_poolEntry) );
                    pNext->nLength = pEntry->nLength - nSize - sizeof( s_poolEntry );
                    pNext->pNext = pEntry->pNext;
                    pNext->nFlags = POOL_UNUSED;

                    pEntry->pNext = pNext;
                    pEntry->nLength = pNext - pEntry;
                }

                return (s_poolEntry*)( (uint32)pEntry + sizeof( s_poolEntry ) );
            }
            else if ( pEntry->pNext == NULL && pEntry->nFlags == POOL_UNUSED )
            {
                // If this is the last entry and its empty we can just resize it
                
                pEntry->nLength = nSize;
                pEntry->nFlags = POOL_USED;

                return (s_poolEntry*)( (uint32)pEntry + sizeof( s_poolEntry ) );
            }

            if ( pEntry->pNext != NULL )
                pEntry = pEntry->pNext;
            else
                bLooping = false;
        }

        // No empty blocks were found, so create a new one

        uint32 nAddress = (uint32)pEntry + pEntry->nLength + sizeof( s_poolEntry );
        nAddress = pool_align( nAddress, nAlignment );

        if ( nAddress + sizeof( s_poolEntry ) + nSize >= pHeader->nEnd )
            return NULL;

        s_poolEntry* pReturn = (s_poolEntry*)nAddress;
        pReturn->pNext = NULL;
        pReturn->nLength = nSize;
        pReturn->nFlags = POOL_USED;

        pEntry->pNext = pReturn;

        return (s_poolEntry*)( (uint32)pReturn + sizeof( s_poolEntry ) );
    }

    // Should never get here, but oh well
    
    return NULL;
}

void pool_free( s_poolHeader* pHeader, void* pMemory )
{
    s_poolEntry* pEntry = (s_poolEntry*)((uint32)pMemory - sizeof( s_poolEntry ) );

    if ( pHeader->pFirst == pEntry && pEntry->pNext == NULL )
    {
        // First and only entry, just delete it in the header
        
        pHeader->pFirst = NULL;
        return;
    }
    else if ( pEntry->pNext == NULL )
    {
        // This is the last entry so we can just delete it
        
        s_poolEntry* pPrevious = pool_findPrevious( pHeader, pEntry );
        pPrevious->pNext = NULL;
    }
    else
    {
        // Middle entry, mark it as unused and resize it to minimize fragmentation
        
        pEntry->nFlags = POOL_UNUSED;
        pEntry->nLength = (uint32)pEntry->pNext - (uint32)pEntry;

        // Combine unused entries

        pool_prune( pHeader );
    }
}

void pool_debugPrint( s_poolHeader* pHeader )
{
    if ( pHeader->pFirst == NULL )
        return;

    s_poolEntry* pEntry = pHeader->pFirst;

    while ( pEntry != NULL )
    {
        serial_writeString( 0, "entry at " );
        serial_writeHex( 0, (uint32)pEntry );
        serial_writeString( 0, " size of " );
        serial_writeHex( 0, pEntry->nLength );
        serial_writeString( 0, " flags " );
        serial_writeHex( 0, pEntry->nFlags );
        serial_writeChar( 0, '\n' );
        
        pEntry = pEntry->pNext;
    }
}
