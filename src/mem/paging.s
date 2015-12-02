[GLOBAL paging_init]

	PAGING_PRESENT		equ 0x1
	PAGING_RW		equ 0x2
	PAGING_READONLY		equ 0x0
	PAGING_USERMODE		equ 0x4
	PAGING_KERNELMODE	equ 0x0
	
paging_init:
	ret
