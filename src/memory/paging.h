#ifndef PAGING_H
#define PAGING_H

#define PAGE_PRESENT            0x1
#define PAGE_WRITABLE           0x2
#define PAGE_USERMODE           0x4
#define PAGE_WRITETHROUGH       0x8
#define PAGE_CACHEDISABLED      0x10
#define PAGE_ACCESSED           0x20
#define PAGE_DIRTY              0x40
#define PAGE_TABLE_4MBPAGES     0x80
#define PAGE_GLOBAL             0x100

typedef struct
{
    uint16 nFlags;
    uint16 nAddress;
} s_page;

typedef struct
{
    s_page pPages[1024];
} s_pageTable;

typedef s_pageTable** s_pageDirectory;

void paging_init( );

#endif
