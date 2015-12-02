[GLOBAL kb_init]
[GLOBAL kb_irq]
[GLOBAL kb_ps2_wait_read]
[GLOBAL kb_ps2_wait_write]
[EXTERN irq_loadHandler]
[EXTERN panic]
[EXTERN screen_printChar]
[EXTERN screen_printHex]
	
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

	
KB_RELEASE		equ 0xF0
KB_MULTIMEDIA		equ 0xE0

	
KB_SCANCODE:
KB_F9:			db 0	;0x01
			db 0	;0x02
KB_F5:			db 0	;0x03
KB_F3:			db 0	;0x04
KB_F1:			db 0	;0x05
KB_F2:			db 0	;0x06
KB_F12:			db 0	;0x07
			db 0	;0x08
KB_F10:			db 0	;0x09
KB_F8:			db 0	;0x0A
KB_F6:			db 0	;0x0B
KB_F4:			db 0	;0x0C
KB_TAB:			db 0	;0x0D
KB_BACKTICK:		db 96	;0x0E
KB_UNUSED3:		db 0	;0x0F
			db 0	;0x10
KB_LALT:		db 0	;0x11
KB_LSHIFT:		db 0	;0x12
			db 0	;0x13
KB_LCONTROL:		db 0	;0x14
KB_Q:			db 'q'	;0x15
KB_1:			db '1'	;0x16
			db 0, 0, 0 ;0x17-0x19
KB_Z:			db 'z'	;0x1A
KB_S:			db 's'	;0x1B
KB_A:			db 'a'	;0x1C
KB_W:			db 'w'	;0x1D
KB_2:			db '2'	;0x1E
			db 0, 0	;0x1F-0x20
KB_C:			db 'c'	;0x21
KB_X:			db 'x'	;0x22
KB_D:			db 'd'	;0x23
KB_E:			db 'e'	;0x24
KB_4:			db '4'	;0x25
KB_3:			db '3'	;0x26
			db 0, 0	;0x27-0x28
KB_SPACE:		db ' '	;0x29
KB_V:			db 'v'	;0x2A
KB_F:			db 'f'	;0x2B
KB_T:			db 't'	;0x2C
KB_R:			db 'r'	;0x2D
KB_5:			db '5'	;0x2E
			db 0, 0	;0x2F-0x30
KB_N:			db 'n'	;0x31
KB_B:			db 'b'	;0x32
KB_H:			db 'h'	;0x33
KB_G:			db 'g'	;0x34
KB_Y:			db 'y'	;0x35
KB_6:			db '6'	;0x36
			db 0, 0, 0	;0x37-0x39
KB_M:			db 'm'	;0x3A
KB_J:			db 'j'	;0x3B
KB_U:			db 'u'	;0x3C
KB_7:			db '7'	;0x3D
KB_8:			db '8'	;0x3E
			db 0, 0	;0x3F-0x40
KB_COMMA:		db ','	;0x41
KB_K:			db 'k'	;0x42
KB_I:			db 'i'	;0x43
KB_O:			db 'o'	;0x44
KB_0:			db '0'	;0x45
KB_9:			db '9'	;0x46
			db 0, 0	;0x47-0x48
KB_PERIOD:		db '.'	;0x49
KB_FORWARDSLASH:	db '/'	;0x4A
KB_L:			db 'l'	;0x4B
KB_SEMICOLON:		db ';'	;0x4C
KB_P:			db 'p'	;0x4D
KB_MINUS:		db '-'	;0x4E
			db 0, 0, 0	;0x4F-0x51
KB_QUOTE:		db 39	;0x52
			db 0	;0x53
KB_LBRACKET:		db '['	;0x54
KB_EQUAL:		db 61	;0x55
			db 0, 0	;0x56-0x57
KB_CAPSLOCK:		db 0	;0x58
KB_RSHIFT:		db 0	;0x59
KB_ENTER:		db 0	;0x5a
KB_RBRACKET:		db ']'	;0x5B
			db 0	;0x5C
KB_BACKSLASH:		db 92	;0x5D
	
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

kb_printScancode:	; [esp+4] - scancode
	mov eax, [esp+4]
	cmp eax, 0x5D
	jle _kb_printScancode

	ret

_kb_printScancode:
	add eax, KB_SCANCODE
	dec eax
	xor edx, edx
	mov dl, byte [eax]
	
	push edx
	call screen_printChar
	add esp, 4
	
	ret
	
kb_poll:
	xor eax, eax
	call kb_ps2_wait_read
	in al, PS2_DATA

	cmp al, KB_RELEASE
	jne _kb_poll_end

	xor eax, eax
	call kb_ps2_wait_read
	in al, PS2_DATA

	cmp al, KB_MULTIMEDIA
	jne _kb_poll_return

	xor eax, eax
	call kb_ps2_wait_read
	in al, PS2_DATA

	jmp _kb_poll_return

_kb_poll_end:	
	
	push eax
	call kb_printScancode
	add esp, 4

_kb_poll_return:	
	ret
	
kb_irq:
	call kb_poll
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
	or al, 0x1		;enable interrupts
	xor al, 0x40		;disable translation

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
