[GLOBAL a20_enable_bios]
[GLOBAL a20_enable_fast]
[EXTERN ps2_wait_read]
[EXTERN ps2_wait_write]
	
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
	
	ret
