[GLOBAL kb_init]
[GLOBAL kb_irq]
[GLOBAL kb_ps2_wait_read]
[GLOBAL kb_ps2_wait_write]
[EXTERN irq_loadHandler]
[EXTERN panic]
[EXTERN screen_printChar]
	
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

KB_SCANCODE:			db 0
KB_SCANCODE_ESCAPE_PRESS:	db 0 ; 0x1
KB_SCANCODE_1_PRESS:		db '1' ;0x2
KB_SCANCODE_2_PRESS:		db '2' ;0x3
KB_SCANCODE_3_PRESS:		db '3' ;0x4
KB_SCANCODE_4_PRESS:		db '4' ;0x5
KB_SCANCODE_5_PRESS:		db '5' ;0x6
KB_SCANCODE_6_PRESS:		db '6' ;0x7
KB_SCANCODE_7_PRESS:		db '7' ;0x8
KB_SCANCODE_8_PRESS:		db '8' ;0x9
KB_SCANCODE_9_PRESS:		db '9' ;0xA
KB_SCANCODE_0_PRESS:		db '0' ;0xB
KB_SCANCODE_MINUS_PRESS:	db '-' ;0xC
KB_SCANCODE_EQUAL_PRESS:	db '=' ;0xD
KB_SCANCODE_BACKSPACE_PRESS:	db '\b' ;0xE
KB_SCANCODE_TAB_PRESS:		db '\t' ;0xF
KB_SCANCODE_Q_PRESS:		db 'q'	;0x10
KB_SCANCODE_W_PRESS:		db 'w'	;0x11
KB_SCANCODE_E_PRESS:		db 'e'	;0x12
KB_SCANCODE_R_PRESS:		db 'r'	;0x13
KB_SCANCODE_T_PRESS:		db 't'	;0x14
KB_SCANCODE_Y_PRESS:		db 'y'	;0x15
KB_SCANCODE_U_PRESS:		db 'u'	;0x16
KB_SCANCODE_I_PRESS:		db 'i'	;0x17
KB_SCANCODE_O_PRESS:		db 'o'	;0x18
KB_SCANCODE_P_PRESS:		db 'p'	;0x19
KB_SCANCODE_LBRACKET_PRESS:	db '['	;0x1A
KB_SCANCODE_RBRACKET_PRESS:	db ']'	;0x1B
KB_SCANCODE_ENTER_PRESS:	db '\n' ;0x1C
KB_SCANCODE_LCONTROL_PRESS:	db 0	;0x1D
KB_SCANCODE_A_PRESS:		db 'a'	;0x1E
KB_SCANCODE_S_PRESS:		db 's'	;0x1F
KB_SCANCODE_D_PRESS:		db 'd'	;0x20
KB_SCANCODE_F_PRESS:		db 'f'	;0x21
KB_SCANCODE_G_PRESS:		db 'g'	;0x22
KB_SCANCODE_H_PRESS:		db 'h'	;0x23
KB_SCANCODE_J_PRESS:		db 'j'	;0x24
KB_SCANCODE_K_PRESS:		db 'k'	;0x25
KB_SCANCODE_L_PRESS:		db 'l'	;0x26
KB_SCANCODE_SEMICOLON_PRESS:	db '\;' ;0x27
KB_SCANCODE_QUOTE_PRESS:	db '\' 	;0x28
KB_SCANCODE_BACKTICK_PRESS:	db '`'	;0x29
KB_SCANCODE_LSHIFT_PRESS:	db 0	;0x2AKB_SCANCODE_BACKSLASH_PRESS:	db '\\'	;0x2B
KB_SCANCODE_Z_PRESS:		db 'z'	;0x2C
KB_SCANCODE_X_PRESS:		db 'x'	;0x2D
KB_SCANCODE_C_PRESS:		db 'c'	;0x2E
KB_SCANCODE_V_PRESS:		db 'v'	;0x2F
KB_SCANCODE_B_PRESS:		db 'b'	;0x30
KB_SCANCODE_N_PRESS:		db 'n'	;0x31
KB_SCANCODE_M_PRESS:		db 'm'	;0x32
KB_SCANCODE_COMMA_PRESS:	db ','	;0x33
KB_SCANCODE_PERIOD_PRESS:	db '.'	;0x34
KB_SCANCODE_FORWARDSLASH_PRESS:	db '/'	;0x35
KB_SCANCODE_RSHIFT_PRESS:	db 0	;0x36
KB_SCANCODE_NP_STAR_PRESS:	db '*'	;0x37
KB_SCANCODE_LALT_PRESS:		db 0	;0x38
KB_SCANCODE_SPACE_PRESS:	db ' '	;0x39
KB_SCANCODE_CAPSLOCK_PRESS:	db 0	;0x3A
KB_SCANCODE_FUNCTION_PRESS:	times 10 db 0 ;0x3B - 0x45
	
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
	cmp eax, 0x45
	jle _kb_printScancode

	ret

_kb_printScancode:
	add eax, KB_SCANCODE
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

	push eax
	call kb_printScancode
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
