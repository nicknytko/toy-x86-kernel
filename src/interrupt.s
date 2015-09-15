	[GLOBAL idt_init]

	IDT_ENTRY_SIZE		equ 8
	IDT_TABLE_ENTRIES	equ 32
	IDT_TABLE_LIMIT		equ (IDT_TABLE_ENTRIES * IDT_ENTRY_SIZE) - 1

%macro IDT_CALL_SET 1
	push %1
	push ISR_%1
	call idt_set
	add esi, 8
%endmacro

%macro ISR_NO_ERROR 1
ISR_%1:
	cli
	push byte 0
	push byte %1
	jmp isr_stub
%endmacro

%macro ISR_ERROR 1
ISR_%1:
	cli
	push byte %1
	jmp isr_stub
%endmacro
	
IDT_TABLE: times (IDT_TABLE_ENTRIES*IDT_ENTRY_SIZE) db 0

;;; structure of idt entry
;;; 0x0-0x1 lower offset (word)
;;; 0x2-0x3 code segment (word)
;;; 0x4     unused (byte)
;;; 0x5     attributes (byte)
;;; 0x6-0x7 higher offset (word)
	
IDT_PTR:
	dw IDT_TABLE_LIMIT
	dd IDT_TABLE

ISR_NO_ERROR 0
ISR_NO_ERROR 1
ISR_NO_ERROR 2
ISR_NO_ERROR 3
ISR_NO_ERROR 4
ISR_NO_ERROR 5
ISR_NO_ERROR 6
ISR_NO_ERROR 7
ISR_ERROR    8
ISR_NO_ERROR 9
ISR_ERROR    10
ISR_ERROR    11
ISR_ERROR    12
ISR_ERROR    13
ISR_ERROR    14
ISR_NO_ERROR 15
ISR_NO_ERROR 16
ISR_NO_ERROR 17
ISR_NO_ERROR 18
ISR_NO_ERROR 19
ISR_NO_ERROR 20
ISR_NO_ERROR 21
ISR_NO_ERROR 22
ISR_NO_ERROR 23
ISR_NO_ERROR 24
ISR_NO_ERROR 25
ISR_NO_ERROR 26
ISR_NO_ERROR 27
ISR_NO_ERROR 28
ISR_NO_ERROR 29
ISR_NO_ERROR 30
ISR_NO_ERROR 31

isr_stub:
	add esp, 8
	sti
	iret
	
idt_set: 			;esi+8 - index, esi+4 - ptr
	mov eax, [esp+8]	;get index
	imul eax, IDT_ENTRY_SIZE
	add eax, IDT_TABLE

	mov ebx, [esp+4]
	and ebx, 0xFFFF

	mov word [eax], bx
	mov word [eax+2], 0x08
	mov byte [eax+5], 0x8E

	mov ebx, [esp+4]
	and ebx, 0xFFFF0000
	shr ebx, 16

	mov word [eax+6], bx
	
	ret
	
idt_init:
	IDT_CALL_SET 0
	IDT_CALL_SET 1
	IDT_CALL_SET 2
	IDT_CALL_SET 3
	IDT_CALL_SET 4
	IDT_CALL_SET 5
	IDT_CALL_SET 6
	IDT_CALL_SET 7
	IDT_CALL_SET 8
	IDT_CALL_SET 9
	IDT_CALL_SET 10
	IDT_CALL_SET 11
	IDT_CALL_SET 12
	IDT_CALL_SET 13
	IDT_CALL_SET 14
	IDT_CALL_SET 15
	IDT_CALL_SET 16
	IDT_CALL_SET 17
	IDT_CALL_SET 18
	IDT_CALL_SET 19
	IDT_CALL_SET 20
	IDT_CALL_SET 21
	IDT_CALL_SET 22
	IDT_CALL_SET 23
	IDT_CALL_SET 24
	IDT_CALL_SET 25
	IDT_CALL_SET 26
	IDT_CALL_SET 27
	IDT_CALL_SET 28
	IDT_CALL_SET 29
	IDT_CALL_SET 30
	IDT_CALL_SET 31
	
	mov eax, IDT_PTR
	lidt [eax]

	ret
