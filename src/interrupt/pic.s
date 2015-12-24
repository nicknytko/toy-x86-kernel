[GLOBAL pic_remap]
[GLOBAL pic_sendEOI]
[GLOBAL pic_IMRDisableAll]
[GLOBAL pic_setIMRMask]
[GLOBAL pic_clearIMRMask]
	
	PIC1_BASE equ 0x20
	PIC2_BASE equ 0xA0
	PIC1_COM  equ PIC1_BASE
	PIC2_COM  equ PIC2_BASE
	PIC1_DATA equ PIC1_BASE+1
	PIC2_DATA equ PIC2_BASE+1

	PIC_EOI   equ 0x20

pic_sendEOI:			; eax - irq number
	cmp eax, 0x28
	jl _pic_sendEOI_pic1

	mov al, PIC_EOI
	out PIC2_COM, al

_pic_sendEOI_pic1:
	mov al, PIC_EOI
	out PIC1_COM, al

	ret

pic_IMRDisableAll:
	mov al, 0xFF
	out PIC1_DATA, al
	out PIC2_DATA, al
	ret
	
pic_setIMRMask:			; [esp+4] - irq number
	mov edx, [esp+4]
	cmp edx, 8
	jge _pic_setIMRMask_slave

	in al, PIC1_DATA
	mov cl, al
	
	mov al, 1
	shl al, cl		;get imr from pic, set n'th bit, and send back
	or al, cl

	out PIC1_DATA, al
	
	ret
	
_pic_setIMRMask_slave:

	in al, PIC2_DATA
	mov cl, al
	
	mov al, 1
	shl al, cl
	or al, cl

	out PIC2_DATA, al
	
	ret

pic_clearIMRMask:			; [esp+4] - irq number
	mov edx, [esp+4]
	cmp edx, 8
	mov cl, dl
	jge _pic_clearIMRMask_slave

	in al, PIC1_DATA
	mov dl, al
	
	mov al, 1
	shl al, cl		;get imr from pic, set n'th bit, and send back
	not al
	and al, dl

	out PIC1_DATA, al
	
	ret
	
_pic_clearIMRMask_slave:

	in al, PIC2_DATA
	mov dl, al
	
	mov al, 1
	sub cl, 8
	shl al, cl
	not al
	and al, dl

	out PIC2_DATA, al

	push 2
	call pic_clearIMRMask
	add esp, 4
	
	ret
	
pic_remap:
	xor eax, eax

	;; save pic masks
	
	in al, PIC1_DATA
	push eax
	in al, PIC2_DATA
	push eax

	;; start initialization
	
	mov al, 0x11
	out PIC1_COM, al
	out PIC2_COM, al

	;; remap pic1 to interrupt 32
	
	mov al, 0x20		
	out PIC1_DATA, al

	;; remap pic2 to interrupt 40
	
	mov al, 0x28		
	out PIC2_DATA, al

	;; tell pic1 that pic2 is at irq2
	
	mov al, 4
	out PIC1_DATA, al

	;; tell pic2 cascade identity
	
	mov al, 2
	out PIC2_DATA, al

	;; 8086/8088 mode
	
	mov al, 1
	out PIC1_DATA, al
	out PIC2_DATA, al

	;; restore saved masks
	
	pop eax
	out PIC2_DATA, al
	pop eax
	out PIC1_DATA, al
	
	ret
