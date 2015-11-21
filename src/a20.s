[GLOBAL a20_enable]
[GLOBAL a20_isEnabled]
[EXTERN kb_ps2_wait_read]
[EXTERN kb_ps2_wait_write]
	
PS2_RW 		equ 0x60
PS2_STATUS 	equ 0x64
PS2_COMMAND	equ 0x64

A20_ENABLED: db 0

a20_check:			;http://wiki.osdev.org/A20#Testing_the_A20_line
	cli

	xor ax, ax
	mov es, ax

	not ax
	mov dx, ax

	mov di, 0x0500
	mov si, 0x0510

	mov al, byte [es:di]
	push ax

	mov al, byte [ds:si]
	push ax

	mov byte [es:di], 0x00
	mov byte [ds:si], 0xFF

	cmp byte [es:di], 0xFF

	pop ax
	mov byte [ds:si], al

	pop ax
	mov byte [es:di], al

	mov ax, 0
	je _a20_check_end

	mov ax, 1

_a20_check_end:
	ret

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
	call a20_check
	cmp ax, 0

	jne _a20_enable_end

	call a20_enable_ps2
	call a20_check
	cmp ax, 0

	je _a20_enabled_fail

_a20_enable_end:
	mov byte [A20_ENABLED], 0x1
	ret

_a20_enabled_fail:
	ret

a20_isEnabled:
	mov al, byte [A20_ENABLED]
	ret
