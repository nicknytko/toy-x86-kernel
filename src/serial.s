[GLOBAL serial_init]
[GLOBAL serial_writeByte]
[GLOBAL serial_writeString]
[GLOBAL serial_readByte]

BDA_COM: equ 0x0400

COM1_PORT: equ 0x3f8
COM_PORTS: db 0

serial_init:
	mov ax, word [BDA_COM]
	
	cmp ax, 0
	je _serial_init_done

	mov al, 0x1
	mov byte [COM_PORTS], al

	mov dx, COM1_PORT+1
	mov al, 0

	out dx, al		;disable interrupts

	mov dx, COM1_PORT+3
	mov al, 0x80
	
	out dx, al		;enable dlab divisor

	mov dx, COM1_PORT
	mov al, 0x03
	
	out dx, al		;set divisor to 3 (low)
	
	mov dx, COM1_PORT+1
	mov al, 0x0

	out dx, al		;set divisor to 3 (high)

	mov dx, COM1_PORT+3
	mov al, 0x03

	out dx, al		;8 bits, no parity, 1 stop

	mov dx, COM1_PORT+2
	mov al, 0xC7

	out dx, al		;enable fifo

	mov dx, COM1_PORT+4
	mov al, 0x0B

	out dx, al		;irq enabled

_serial_init_done:
	ret


serial_readByte:
	mov dx, COM1_PORT+5

_serial_readByte_loop:
	in al, dx
	cmp al, 0
	je _serial_readByte_loop

	ret

serial_writeByte:
	pop eax
	pop ebx
	push eax

	mov dx, COM1_PORT+5

_serial_writeByte_loop:
	in al, dx
	and al, 0x20

	cmp al, 0
	je _serial_writeByte_loop

	mov dx, COM1_PORT
	mov al, bl

	out dx, al

	ret

serial_writeString:
	pop eax
	pop esi
	push eax

	xor eax, eax

_serial_writeString_loop:
	mov al, byte [esi]
	cmp al, 0
	je _serial_writeString_endloop

	push eax
	call serial_writeByte

	inc esi
	jmp _serial_writeString_loop

_serial_writeString_endloop:
	ret
