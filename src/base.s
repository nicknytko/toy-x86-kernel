[GLOBAL inb]
[GLOBAL outb]

inb:				;esp+4 - port
	mov edx, [esp+4]
	in al, dx
	ret

inw:				;esp+4 - port
	mov edx, [esp+4]
	in ax, dx
	ret
	
outb:				;esp+4 - port, esp+8 - value
	mov edx, [esp+4]
	mov eax, [esp+8]
	out dx, al
	ret
