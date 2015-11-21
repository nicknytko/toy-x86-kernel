[GLOBAL idt_init]
[GLOBAL irq_loadHandler]
[EXTERN pic_remap]
[EXTERN pic_sendEOI]
[EXTERN pic_setIMRMask]
	
	IDT_ENTRY_SIZE		equ 8
	IDT_TABLE_ENTRIES	equ 48
	IDT_TABLE_LIMIT		equ (IDT_TABLE_ENTRIES * IDT_ENTRY_SIZE) - 1

%macro IDT_CALL_SET 1
	mov eax, %1
	mov ebx, ISR_%1
	call idt_set
%endmacro

%macro IRQ_CALL_SET 1
	mov eax, %1
	mov ebx, IRQ_%1
	call idt_set
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

IRQ_TABLE: times 16 dd 0	;table of all the irq handlers

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
	add esp, 8
	sti
	iret

irq_stub:
	pusha
	mov eax, [esp+32]

	call pic_sendEOI

	sub eax, 32	;get irq from table
	imul eax, 4
	add eax, IRQ_TABLE

	mov edx, [eax]
	cmp edx, 0
	je _irq_stub_nohandler
	
	call edx
	
_irq_stub_nohandler:	
	popa
	add esp, 8
	sti
	
	iret

irq_loadHandler:	; [esp+8] - irq number, [esp+4] - ptr to handler
	;; load in our table of pointers

	mov eax, [esp+8]
	mov ebx, [esp+4]

	imul eax, 4
	add eax, IRQ_TABLE
	mov dword [eax], ebx

	mov eax, [esp+8]
	push eax
	call pic_setIMRMask
	add esp, 4
	
	ret
	
idt_set: 			;eax - index in idt table, ebx - pointer to isr
	imul eax, IDT_ENTRY_SIZE
	add eax, IDT_TABLE

	mov ecx, ebx
	and ecx, 0xFFFF

	mov word [eax], cx
	mov word [eax+2], 0x08
	mov byte [eax+5], 0x8E

	mov ecx, ebx
	and ecx, 0xFFFF0000
	shr ecx, 16

	mov word [eax+6], cx
	
	ret
	
idt_init:
	call pic_remap
	
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
	
	mov eax, IDT_PTR
	lidt [eax]

	sti

	ret
