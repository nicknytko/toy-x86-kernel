[GLOBAL panic]
[EXTERN screen_printString]
[EXTERN screen_printHex]
[EXTERN screen_tab]
[EXTERN screen_newline]

KERNEL_PANIC_STRING: db 'Kernel Panic! ', 0
P_EAX: db 'EAX ', 0
P_EBX: db 'EBX ', 0
P_ECX: db 'ECX ', 0
P_EDX: db 'EDX ', 0
P_ESP: db 'ESP ', 0
P_EBP: db 'EBP ', 0
P_ESI: db 'ESI ', 0
P_EDI: db 'EDI ', 0

panic: ;[esi-4] - string for reason
;	pop eax
;	pop esi
;	push eax
	pushad

	mov esi, [esp+36]

	call screen_newline
	call screen_newline
	
	push esi
	push KERNEL_PANIC_STRING

	call screen_printString	;kernel panic string
	call screen_printString ;reason string

	call screen_newline
	call screen_newline

;;print registers
;;eax
	push P_EAX
	call screen_printString

	mov eax, [esp+28]
	push eax
	call screen_printHex

	call screen_newline

;;ecx

	push P_ECX
	call screen_printString

	mov eax, [esp+24]
	push eax
	call screen_printHex

	call screen_newline

;;edx

	push P_EDX
	call screen_printString

	mov eax, [esp+20]
	push eax
	call screen_printHex

	call screen_newline

;;ebx

	push P_EBX
	call screen_printString

	mov eax, [esp+16]
	push eax
	call screen_printHex

	call screen_newline
	call screen_newline

;;esp

	push P_ESP
	call screen_printString

	mov eax, [esp+12]
	push eax
	call screen_printHex

	call screen_newline

;;ebp

	push P_EBP
	call screen_printString

	mov eax, [esp+8]
	push eax
	call screen_printHex

	call screen_newline

;;esi

	push P_ESI
	call screen_printString

	mov eax, [esp+4]
	push eax
	call screen_printHex

	call screen_newline

;;edi

	push P_EDI
	call screen_printString

	mov eax, [esp]
	push eax
	call screen_printHex

	call screen_newline

	popad

	cli			;disable interrupts
_panic_infloop:
	jmp _panic_infloop
