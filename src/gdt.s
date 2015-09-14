SECTION .bss

	GDT_ENTRY_SIZE		equ 8
	GDT_TABLE_ENTRIES 	equ 5
	GDT_TABLE_LIMIT 	equ (GDT_ENTRY_SIZE * GDT_TABLE_ENTRIES) - 1
	
GDT_TABLE:	resb (GDT_TABLE_LIMIT + 1)
GDT_PTR:	resb 6

SECTION .text
	
gdt_init:
	mov eax, GDT_PTR
	mov word [GDT_PTR], GDT_TABLE_LIMIT
	mov dword [GDT_PTR + 2], GDT_TABLE

	mov eax, GDT_PTR
	call gdt_flush
	
gdt_flush:			;pass pointer to gdt table as eax
	lgdt [eax]

	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	jmp 0x8:_gdt_flush

_gdt_flush:
	ret
