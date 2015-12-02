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
	
outb:				;esp+4 - value, esp+8 - port
	mov edx, [esp+8]
	mov eax, [esp+4]
	out dx, al
	ret
