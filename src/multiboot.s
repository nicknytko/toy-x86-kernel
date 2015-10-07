[GLOBAL mboot_setinfo]
[GLOBAL mboot_totalRam]
[GLOBAL mboot_bootDevice]
[GLOBAL mboot_bootName]
[GLOBAL mboot_cmdline]
[GLOBAL mboot_modsNum]
[GLOBAL mboot_modsPtr]
[GLOBAL mboot_memmapLen]
[GLOBAL mboot_memmapPtr]
[GLOBAL mboot_drivesLen]
[GLOBAL mboot_drivesPtr]
[GLOBAL mboot_configTable]
[GLOBAL mboot_apmTable]

MULTIBOOT_INFO: dd 0

MULTIBOOT_MEMSIZE_PRESENT: db 0
MULTIBOOT_BOOTDEV_PRESENT: db 0
MULTIBOOT_CMDLINE_PRESENT: db 0
MULTIBOOT_MODS_PRESENT: db 0
MULTIBOOT_SYMS_PRESENT: db 0
MULTIBOOT_MMAP_PRESENT: db 0
MULTIBOOT_DRIVES_PRESENT: db 0
MULTIBOOT_CONFIGTAB_PRESENT: db 0
MULTIBOOT_BOOTLOADER_NAME_PRESENT: db 0
MULTIBOOT_APMTAB_PRESENT: db 0
MULTIBOOT_VPE_PRESENT: db 0

%macro CHECK_IF_PRESENT 2
	mov eax, %1
	mov bl, byte [eax]
	cmp bl, 1
	je _check_if_present_%1%2
	mov eax, 0
	ret
	_check_if_present_%1%2:
%endmacro

mboot_setinfo:		; ebx - multiboot info pointer
	mov eax, MULTIBOOT_INFO
	mov dword [eax], ebx

_multiboot_setinfo_1:
	mov eax, dword [ebx]	;flags
	test eax, 0x1
	je _multiboot_setinfo_2

	mov ecx, MULTIBOOT_MEMSIZE_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_2:
	test eax, 0x2
	je _multiboot_setinfo_3
	
	mov ecx, MULTIBOOT_BOOTDEV_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_3:
	test eax, 0x4
	je _multiboot_setinfo_4

	mov ecx, MULTIBOOT_CMDLINE_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_4:
	test eax, 0x8
	je _multiboot_setinfo_5

	mov ecx, MULTIBOOT_MODS_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_5:
	test eax, 0x10
	je _multiboot_setinfo_6

	mov ecx, MULTIBOOT_SYMS_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_6:
	test eax, 0x20
	je _multiboot_setinfo_7

	mov ecx, MULTIBOOT_SYMS_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_7:
	test eax, 0x40
	je _multiboot_setinfo_8

	mov ecx, MULTIBOOT_MMAP_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_8:
	test eax, 0x80
	je _multiboot_setinfo_9

	mov ecx, MULTIBOOT_DRIVES_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_9:
	test eax, 0x100
	je _multiboot_setinfo_10

	mov ecx, MULTIBOOT_CONFIGTAB_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_10:
	test eax, 0x200
	je _multiboot_setinfo_11

	mov ecx, MULTIBOOT_BOOTLOADER_NAME_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_11:
	test eax, 0x400
	je _multiboot_setinfo_12

	mov ecx, MULTIBOOT_APMTAB_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_12:
	test eax, 0x800
	je _multiboot_setinfo_end

	mov ecx, MULTIBOOT_VPE_PRESENT
	mov byte [ecx], 1

_multiboot_setinfo_end:
	ret

mboot_totalRam:
	CHECK_IF_PRESENT MULTIBOOT_MEMSIZE_PRESENT, __LINE__

	mov edx, [MULTIBOOT_INFO]
	mov eax, dword [edx+4]
	mov ebx, dword [edx+8]

	add eax, ebx

	ret

mboot_modsNum:
	CHECK_IF_PRESENT MULTIBOOT_MODS_PRESENT, __LINE__
	
	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+20]

	ret

mboot_modsPtr:
	CHECK_IF_PRESENT MULTIBOOT_MODS_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+24]

	ret

mboot_bootName:
	CHECK_IF_PRESENT MULTIBOOT_BOOTLOADER_NAME_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+64]

	ret
