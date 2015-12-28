[GLOBAL idt_init]
[GLOBAL irq_loadHandler]
[GLOBAL nmi_enable]
[GLOBAL nmi_disable]
[GLOBAL int_sti]	
[GLOBAL int_cli]
[GLOBAL IDT_TABLE]
[GLOBAL IRQ_TABLE]
[EXTERN idt_set]
[EXTERN isr_handler]
[EXTERN pic_remap]
[EXTERN pic_sendEOI]
[EXTERN pic_IMRDisableAll]	
[EXTERN syscall_stub]
	
IDT_ENTRY_SIZE		equ 8
IDT_TABLE_ENTRIES	equ 256
IDT_TABLE_LIMIT		equ (IDT_TABLE_ENTRIES * IDT_ENTRY_SIZE) - 1

NMI_REGISTER		equ 0x70

;;; Various tables for holding handlers

SECTION .bss
	
IDT_TABLE: resb (IDT_TABLE_ENTRIES*IDT_ENTRY_SIZE)
IRQ_TABLE: resb 16

SECTION .data
	
IDT_PTR:
	dw IDT_TABLE_LIMIT
	dd IDT_TABLE

SECTION .text
	
;;; Macros for setting and creating handlers
	
%macro IDT_CALL_SET 1
	push ISR_%1
	push %1
	call idt_set
	add esp, 8
%endmacro

%macro IRQ_CALL_SET 1
	push IRQ_%1
	push %1
	call idt_set
	add esp, 8
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
	
%macro IRQ 1
IRQ_%1:
	cli
	push byte 0
	push byte %1
	jmp irq_stub
%endmacro
	
;;; All of our stub interrupt Handlers
	
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
IRQ          32
IRQ          33
IRQ          34
IRQ          35
IRQ          36
IRQ          37
IRQ          38
IRQ          39
IRQ          40
IRQ          41
IRQ          42
IRQ          43
IRQ          44
IRQ          45
IRQ          46
IRQ          47

isr_stub:
	call isr_handler
	add esp, 8
	sti
	iret

irq_stub:
	pusha

	;; always send an end-of-interrupt

	mov eax, [esp+32]
	push eax
	call pic_sendEOI
	add esp, 4

	;; get IRQ from table
	
	mov eax, [esp+32]
	sub eax, 32
	mov edx, [IRQ_TABLE + eax*4]

	;; check if we have a handler
	
	cmp edx, 0
	je _irq_stub_nohandler
	
	call edx
	
_irq_stub_nohandler:	
	popa
	add esp, 8
	sti
	
	iret

int_cli:
	cli
	call nmi_disable
	ret

int_sti:
	sti
	call nmi_enable
	ret

nmi_enable:
	mov dx, NMI_REGISTER
	in al, dx
	and al, 0x7F
	out dx, al
	ret

nmi_disable:
	mov dx, NMI_REGISTER
	in al, dx
	or al, 0x80
	out dx, al
	ret
	
idt_init:
	
	;; Set up our pic, have every IRQ disabled by default
	
	call pic_remap
	call pic_IMRDisableAll

	;; Setup our interrupts
	
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
	IRQ_CALL_SET 32
	IRQ_CALL_SET 33
	IRQ_CALL_SET 34
	IRQ_CALL_SET 35
	IRQ_CALL_SET 36
	IRQ_CALL_SET 37
	IRQ_CALL_SET 38
	IRQ_CALL_SET 39
	IRQ_CALL_SET 40
	IRQ_CALL_SET 41
	IRQ_CALL_SET 42
	IRQ_CALL_SET 43
	IRQ_CALL_SET 44
	IRQ_CALL_SET 45
	IRQ_CALL_SET 46
	IRQ_CALL_SET 47

	;; Load our IDT and restore interrupts
	
	mov eax, IDT_PTR
	lidt [eax]

	sti

	ret
