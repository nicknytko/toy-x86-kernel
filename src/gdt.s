	GDT_ENTRY_SIZE		equ 8
	GDT_TABLE_ENTRIES 	equ 3
	GDT_TABLE_LIMIT 	equ (GDT_ENTRY_SIZE * GDT_TABLE_ENTRIES) - 1
	
GDT_TABLE:	times (GDT_TABLE_LIMIT + 1) db 0
	
GDT_TABLE_NULL:
	times 2 dd 0

GDT_TABLE_CODE:
	dw 0xFFFF		;lower limit
	dw 0			;base low
	db 0			;base middle
	db 0x9A			;access
	db 0xCF			;granularity
	db 0			;base high

GDT_TABLE_DATA:
	dw 0xFFFF
	dw 0
	db 0
	db 0x92
	db 0xCF
	db 0

GDT_PTR:
	dw GDT_TABLE_LIMIT
	dd GDT_TABLE_NULL
	
[GLOBAL gdt_init]
	
gdt_init:
	mov eax, GDT_PTR
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x08:_gdt_init_flush

_gdt_init_flush:
	ret
