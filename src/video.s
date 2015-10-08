	[GLOBAL screen_clear]
	[GLOBAL screen_setCursor]
	[GLOBAL screen_newline]
	[GLOBAL screen_tab]
	[GLOBAL screen_printString]
	[GLOBAL screen_printHex]
	[GLOBAL screen_printDec]
	[GLOBAL screen_scroll]

	VGA_WIDTH	equ	80
	VGA_HEIGHT	equ	25

	VGA_OFFSET	equ	0xB8000
	VGA_END		equ	VGA_OFFSET + (VGA_WIDTH*VGA_HEIGHT)*2

	VGA_BLANK       equ     0xF00
	
VGA_CURSOR_X:		dd 	0
VGA_CURSOR_Y:		dd	0
	
screen_clear:
	mov eax, VGA_OFFSET
_screen_clear_loop:
	mov word [eax], VGA_BLANK
	add eax, 2
	cmp eax, VGA_END
	jne _screen_clear_loop

	push 0
	push 0
	call screen_setCursor
	add esp, 8

	ret

screen_setCursor:
	mov ebx, [esp+4] 	;cursor x
	mov ecx, [esp+8]	;cursor y

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

screen_scroll:
	mov eax, VGA_OFFSET
	mov ebx, (VGA_OFFSET + (VGA_WIDTH * (VGA_HEIGHT-1)))

_screen_scroll_loop:
	mov dx, word [eax + VGA_WIDTH*2]
	mov word [eax], dx

	add eax, 2
	cmp eax, ebx
	jl _screen_scroll_loop

	mov ebx, (VGA_OFFSET + (VGA_WIDTH * VGA_HEIGHT))

_screen_scroll_lastline:
	mov word [eax], VGA_BLANK
	add eax, 2

	cmp eax, ebx
	jl _screen_scroll_lastline

	mov eax, dword [VGA_CURSOR_Y]
	mov ebx, dword [VGA_CURSOR_X]

	dec eax

	push eax
	push ebx

	call screen_setCursor
	add esp, 8

	ret

screen_newline:
	mov eax, dword [VGA_CURSOR_Y]
	inc eax

	mov dword [VGA_CURSOR_Y], eax
	mov dword [VGA_CURSOR_X], 0

	push eax
	push 0

	call screen_setCursor
	add esp, 8
	ret

screen_tab:
	mov eax, dword [VGA_CURSOR_X]
	mov ebx, dword [VGA_CURSOR_Y]

	xor edx, edx
	mov ebx, 8
	div ebx
	inc eax
	imul eax, ebx

	push ebx
	push eax

	call screen_setCursor
	add esp, 8
	ret

screen_printHex:
	mov eax, [esp+4]

	mov ebx, dword [VGA_CURSOR_X]
	mov ecx, dword [VGA_CURSOR_Y]

	mov edx, eax

	mov eax, ecx
	imul eax, VGA_WIDTH
	add eax, ebx
	imul eax, 2
	add eax, VGA_OFFSET

	mov ebx, edx

	mov byte [eax], 0x30
	mov byte [eax+1], 0xF
	mov byte [eax+2], 0x78
	mov byte [eax+3], 0xF
	add eax, 4

	mov edx, eax
	add eax, 14

_screen_printHex_loop:
	cmp eax, edx
	jl _screen_printHex_endLoop

	mov ecx, ebx
	and ecx, 0xF
	shr ebx, 4

	cmp ecx, 10
	jge _screen_printHex_printLetter

_screen_printHex_printNum:
	add ecx, 48
	mov byte [eax], cl
	dec eax
	mov byte [eax], 0xF
	dec eax

	jmp _screen_printHex_loop

_screen_printHex_printLetter:
	add ecx, 55
	mov byte [eax], cl
	dec eax
	mov byte [eax], 0xF
	dec eax

	jmp _screen_printHex_loop

_screen_printHex_endLoop:
	add eax, 18

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
	add esp, 8
	
	ret

screen_printDec:
	mov edx, [esp+4]

	mov ebx, dword [VGA_CURSOR_X]
	mov ecx, dword [VGA_CURSOR_Y]

	mov eax, ecx
	imul eax, VGA_WIDTH
	add eax, ebx
	imul eax, 2
	add eax, VGA_OFFSET

	push eax		; starting memory cell
	mov eax, edx
	push eax		; number
	mov ebx, 10
	mov ecx, 0

_screen_printDec_countDigits:
	xor edx, edx
	div ebx

	inc ecx

	cmp eax, 0
	jg _screen_printDec_countDigits

	pop eax			; number
	pop ebx			; starting memory cell
	
	dec ecx
	imul ecx, 2
	add ecx, ebx		; iterator / ending memory cell

	push ecx

_screen_printDec_printDigits:
	xor edx, edx

	push ebx
	mov ebx, 10
	div ebx
	pop ebx

	add dl, 48
	mov byte [ecx], dl
	mov byte [ecx+1], 0xF

	sub ecx, 2

	cmp ecx, ebx
	jge _screen_printDec_printDigits

	pop eax
	add eax, 2

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
	add esp, 8

	ret

screen_printString:
;	pop eax
;	pop esi			;get string pointer
;	push eax

	mov esi, [esp+4]

	cmp esi, 0
	jne _screen_printString_sanityCheck
	
	ret

_screen_printString_sanityCheck:

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
	add esp, 8

	ret
