	[GLOBAL screen_clear]
	[GLOBAL screen_setCursor]

	VGA_COLUMNS	equ	80
	VGA_ROWS	equ	25

	VGA_OFFSET	equ	0xB8000
	VGA_END		equ	VGA_OFFSET + (VGA_ROWS*VGA_COLUMNS)*2

	VGA_CURSOR_X	equ 	0x500
	VGA_CURSOR_Y	equ	0x504
	
screen_clear:
	mov eax, VGA_OFFSET
_screen_clear_loop:
	mov word [eax], 0xF00
	add eax, 2	
	cmp eax, VGA_END
	jne _screen_clear_loop
	ret

screen_setCursor:
	mov ebx, [esp+4]	;get cursor x
	mov ecx, [esp+8]	;get cursor y
	mov ax, cx		;set ax to cursor y
	imul ax, 80		;multiply cursor y by rows (80)
	add ax, bx		;add cursor x
	
	mov bx, ax		;set bx to low byte
	mov cx, ax	
	shr cx, 8		;set cx to high byte
	
	mov dx, 0x3d4
	mov al, 14
	out dx, al

	mov dx, 0x3d5
	mov al, cl
	out dx, al

	mov dx, 0x3d4
	mov al, 15
	out dx, al

	mov dx, 0x3d5
	mov al, bl
	out dx, al
	
	ret
