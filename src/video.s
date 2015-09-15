	[GLOBAL screen_clear]
	[GLOBAL screen_setCursor]
	[GLOBAL screen_printString]

	VGA_WIDTH	equ	80
	VGA_HEIGHT	equ	25

	VGA_OFFSET	equ	0xB8000
	VGA_END		equ	VGA_OFFSET + (VGA_WIDTH*VGA_HEIGHT)*2
	
VGA_CURSOR_X:		dd 	0
VGA_CURSOR_Y:		dd	0
	
screen_clear:
	mov eax, VGA_OFFSET
_screen_clear_loop:
	mov word [eax], 0xF00
	add eax, 2
	cmp eax, VGA_END
	jne _screen_clear_loop
	ret

screen_setCursor:
	pop eax
	pop ebx	                ;pop cursor x
	pop ecx	                ;pop cursor y
	push eax

	mov dword [VGA_CURSOR_X], ebx
	mov dword [VGA_CURSOR_Y], ecx
	
	mov ax, cx		;set ax to cursor y
	imul ax, VGA_WIDTH	;multiply cursor y by rows (80)
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

screen_printString:
	pop eax
	pop esi			;get string pointer
	push eax

	mov ebx, dword [VGA_CURSOR_X]
	mov ecx, dword [VGA_CURSOR_Y]
	
	mov eax, ecx
	imul eax, VGA_WIDTH
	add eax, ebx
	imul eax, 2
	add eax, VGA_OFFSET
	
_screen_printString_loop:
	mov edx, [esi]

	cmp dl, 0		;exit loop if we hit the null terminator
	jz _screen_printString_endLoop

	cmp dl, 9		;handle tab
	je _screen_printString_tabstop
	
	cmp dl, 10		;handle newline
	je _screen_printString_newline
	
	mov byte [eax], dl 	;draw to screen

	add eax, 2		;advance screen memory by two bytes
	inc esi			;increase our string pointer

	jmp _screen_printString_loop

_screen_printString_newline:
	sub eax, VGA_OFFSET
	mov ebx, VGA_WIDTH
	imul ebx, 2

	xor edx, edx		;we will likely overflow so edx should be zero
	div ebx	

	inc eax
	imul eax, VGA_WIDTH
	imul eax, 2
	add eax, VGA_OFFSET
	
	inc esi
	jmp _screen_printString_loop

_screen_printString_tabstop:
	sub eax, VGA_OFFSET
	mov ebx, 16

	xor edx, edx
	div ebx

	inc eax
	imul eax, 16
	add eax, VGA_OFFSET

	inc esi
	jmp _screen_printString_loop
	
_screen_printString_endLoop:	
	sub eax, VGA_OFFSET
	xor edx, edx
	mov ebx, 2
	div ebx
	
	xor edx, edx
	mov ebx, VGA_WIDTH
	div ebx
	
	push eax
	push edx
	call screen_setCursor
	
	ret
