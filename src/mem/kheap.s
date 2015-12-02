[GLOBAL kheap_init]
[GLOBAL kmalloc_a]
[GLOBAL kmalloc_setHeap]
[EXTERN end]

HEAP_ADDRESS: dd 0

kheap_init:
	mov eax, end
	mov dword [HEAP_ADDRESS], eax
	ret

;; in: [esp+4] - size
;; out: eax - address
kmalloc:
	mov ecx, [esp+4]
	
	mov eax, dword [HEAP_ADDRESS]
	mov ebx, eax
	add ebx, ecx

	mov dword [HEAP_ADDRESS], ebx
	ret

;; in: [esp+4] - size
;; out: eax - address
;; allocate memory aligned to a page
kmalloc_a:
	mov ecx, [esp+4]

	mov eax, dword [HEAP_ADDRESS]
	and eax, 0xFFFFF000 	;round down to page
	add eax, 0x1000 	;go to next page

	mov ebx, eax
	add ebx, ecx

	mov dword [HEAP_ADDRESS], ebx
	ret
