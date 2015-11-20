[GLOBAL initrd_load]
[GLOBAL initrd_getNumFiles]
[GLOBAL initrd_file_read]
[GLOBAL initrd_file_write]
[GLOBAL initrd_file_open]
[GLOBAL initrd_file_close]

[EXTERN mboot_modsPtr]
	
INITRD_LOCATION:		dd 0
INITRD_HEADERS_LOCATION:	dd 0

initrd_getNumFiles:
	mov edx, INITRD_LOCATION
	add edx, 4
	mov eax, dword [edx]

	ret
	
initrd_load:
	call mboot_modsPtr

	mov edx, dword [eax]
	cmp edx, 0xDEADBEEF

	je _initrd_load_magic
	mov eax, 0
	ret
	
_initrd_load_magic:	
	mov edx, INITRD_LOCATION
	mov dword [edx], eax

	add eax, 8
	mov edx, INITRD_HEADERS_LOCATION
	
	mov eax, 1
	ret
