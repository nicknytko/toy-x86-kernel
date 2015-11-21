[GLOBAL kb_init]
[GLOBAL kb_irq]
[GLOBAL kb_ps2_wait_read]
[GLOBAL kb_ps2_wait_write]
[EXTERN irq_loadHandler]
[EXTERN panic]
[EXTERN screen_printDec]
	
PS2_AUX_AVAILABLE:	db 0
PS2_SELFTEST_FAIL:	db 'Failed PS/2 self-test.', 0
	
PS2_DATA		equ 0x60
PS2_COMMAND		equ 0x64
PS2_STATUS		equ 0x64
	
PS2_ACK			equ 0xFA
	
PS2_COM_DISABLE_AUX 	equ 0xA7
PS2_COM_ENABLE_AUX	equ 0xA8	
	
PS2_COM_DISABLE 	equ 0xAD
PS2_COM_ENABLE		equ 0xAE

PS2_COM_READ_COMMAND	equ 0x20
PS2_COM_WRITE_COMMAND	equ 0x60	

PS2_COM_SELFTEST	equ 0xAA
	
kb_ps2_wait_read:
	in al, PS2_STATUS
	test al, 0x1
	jz kb_ps2_wait_read
	ret

kb_ps2_wait_write:
	in al, PS2_STATUS
	test al, 0x2
	jnz kb_ps2_wait_write
	ret
	
kb_poll:
	xor eax, eax
	call kb_ps2_wait_read
	in al, PS2_DATA

	push eax
	call screen_printDec
	add esp, 4
	ret
	
kb_irq:
	call kb_poll
	ret

_kb_init:
	push 1
	push kb_irq
	call irq_loadHandler
	add esp, 8

	ret
	
kb_init:
	;; disable auxilliary devices
	
	call kb_ps2_wait_write
	mov al, PS2_COM_DISABLE_AUX
	out PS2_COMMAND, al

	;; disable keyboard
	
	call kb_ps2_wait_write
	mov al, PS2_COM_DISABLE
	out PS2_COMMAND, al

	;; check keyboard command byte
	
	call kb_ps2_wait_write
	mov al, PS2_COM_READ_COMMAND
	out PS2_COMMAND, al

	call kb_ps2_wait_read
	in al, PS2_DATA
	push eax		;save this byte for later
	
	;; test if auxilliary devices are available
	
	test al, 0x10
	jz _kb_init_noaux
	
	mov eax, PS2_AUX_AVAILABLE
	mov byte [eax], 1
	
_kb_init_noaux:	

	;; start keyboard self test
	
	call kb_ps2_wait_write
	mov al, PS2_COM_SELFTEST
	out PS2_COMMAND, al

	call kb_ps2_wait_read
	in al, PS2_DATA

	cmp al, 0x55		;if the self test is successful then AL will be 0x55
	je _kb_init_testpass

	push PS2_SELFTEST_FAIL
	call panic
	
_kb_init_testpass:	

	;; enable interrupts by setting the smallest bit in the command byte
	
	call kb_ps2_wait_write
	mov al, PS2_COM_WRITE_COMMAND
	out PS2_COMMAND, al
	
	call kb_ps2_wait_write
	pop eax
	or al, 0x1
	out PS2_DATA, al

	;; set the keyboard irq

	push 1
	push kb_irq
	call irq_loadHandler
	add esp, 8
	
	;; re-enable the keyboard

	call kb_ps2_wait_write
	mov al, PS2_COM_ENABLE
	out PS2_COMMAND, al

	ret
