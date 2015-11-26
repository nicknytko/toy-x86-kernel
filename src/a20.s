[GLOBAL a20_enable]
[GLOBAL a20_isEnabled]
[EXTERN kb_ps2_wait_read]
[EXTERN kb_ps2_wait_write]
	
PS2_RW 		equ 0x60
PS2_STATUS 	equ 0x64
PS2_COMMAND	equ 0x64

a20_enable_bios:
	[BITS 16]
	mov ax, 0x2401
	int 0x15
	[BITS 32]
	
	xor eax, eax
	jc _a20_enable_bios_fail
	
	mov eax, 1

_a20_enable_bios_fail:	
	ret

a20_enable_fast:
	in al, 0x92
	or al, 0x2
	out 0x92, al
	
a20_enable_ps2:			;enable the a20 line using the ps2 controller
	cli

	call kb_ps2_wait_write
	mov al, 0xAD
	out PS2_COMMAND, al

	call kb_ps2_wait_write
	mov al, 0xD0
	out PS2_COMMAND, al

	call kb_ps2_wait_read
	xor eax, eax
	in al, PS2_RW
	push eax

	call kb_ps2_wait_write
	mov al, 0xD1
	out PS2_COMMAND, al

	call kb_ps2_wait_write
	pop eax
	or al, 2
	out PS2_RW, al

	call kb_ps2_wait_write
	mov al, 0xAE
	out PS2_COMMAND, al
	sti

	ret

a20_enable:
	;; try to first enable a20 through bios
	call a20_enable_bios
	cmp ax, 1
	je _a20_enable_end

	;; check if ps2 controller is working
	in al, PS2_STATUS
	mov dl, al
	in al, PS2_RW
	and al, dl
	cmp al, 0xFF

	;; if so, initialize using ps2 controller
	jne _a20_enable_ps2controller

	;; if not, try fast a20
	call a20_enable_fast
	ret
	
_a20_enable_ps2controller:	
	
	call a20_enable_ps2
	cmp ax, 0

_a20_enable_end:
	ret
