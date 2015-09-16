[GLOBAL kmalloc]
[GLOBAL kmalloc_a]
[GLOBAL kmalloc_setHeap]

HEAP_ADDRESS: dd 0

;; in: [esp-4] - starting address
kmalloc_setHeap: 
	pop ebx
	pop eax	
	push ebx

	mov dword [HEAP_ADDRESS], eax
	ret

;; in: [esp-4] - size
;; out: eax - address
kmalloc:
	pop eax
	pop ecx
	push eax
	
	mov eax, dword [HEAP_ADDRESS]
	mov ebx, eax
	add ebx, ecx

	mov dword [HEAP_ADDRESS], ebx
	ret

;; in: [esp-4] - size
;; out: eax - address
;; allocate memory aligned to a page
kmalloc_a:
	pop eax
	pop ecx
	push eax

	mov eax, dword [HEAP_ADDRESS]
	and eax, 0xFFFFF000 	;round down to page
	add eax, 0x1000 	;go to next page

	mov ebx, eax
	add ebx, ecx

	mov dword [HEAP_ADDRESS], ebx
	ret
