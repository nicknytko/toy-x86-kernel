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

MULTIBOOT_MEMSIZE_PRESENT 		equ 0x1
MULTIBOOT_BOOTDEV_PRESENT 		equ 0x2
MULTIBOOT_CMDLINE_PRESENT		equ 0x4
MULTIBOOT_MODS_PRESENT			equ 0x8
MULTIBOOT_SYMS_PRESENT			equ 0x10
MULTIBOOT_SYMS2_PRESENT			equ 0x20
MULTIBOOT_MMAP_PRESENT			equ 0x40
MULTIBOOT_DRIVES_PRESENT		equ 0x80
MULTIBOOT_CONFIGTAB_PRESENT		equ 0x100
MULTIBOOT_BOOTLOADER_NAME_PRESENT	equ 0x200
MULTIBOOT_APMTAB_PRESENT		equ 0x400
MULTIBOOT_VPE_PRESENT			equ 0x800

%macro CHECK_IF_PRESENT 2
	mov eax, MULTIBOOT_INFO
	mov ebx, dword [eax]
	test ebx, %1

	je _check_if_present_%1%2
	mov eax, 0
	ret
	_check_if_present_%1%2:
%endmacro

mboot_setinfo:		; ebx - multiboot info pointer
	mov eax, MULTIBOOT_INFO
	mov dword [eax], ebx

	ret

;; Get total ram in kilobytes
mboot_totalRam:
	CHECK_IF_PRESENT MULTIBOOT_MEMSIZE_PRESENT, __LINE__

	mov edx, [MULTIBOOT_INFO]
	mov eax, dword [edx+4]
	mov ebx, dword [edx+8]

	add eax, ebx

	ret

;; Get root partition?
mboot_bootDevice:
	CHECK_IF_PRESENT MULTIBOOT_BOOTDEV_PRESENT, __LINE__
	
	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+12]

	ret

;; Get kernel command line arguments
mboot_cmdline:
	CHECK_IF_PRESENT MULTIBOOT_CMDLINE_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+16]

	ret

;; Return pointer to the name of the bootloader
mboot_bootName:
	CHECK_IF_PRESENT MULTIBOOT_BOOTLOADER_NAME_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+64]

	ret

;; Get number of modules
mboot_modsNum:
	CHECK_IF_PRESENT MULTIBOOT_MODS_PRESENT, __LINE__
	
	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+20]

	ret

;; Returns address to array of pointers to modules
mboot_modsPtr:
	CHECK_IF_PRESENT MULTIBOOT_MODS_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+24]

	ret

mboot_memmapLen:
	CHECK_IF_PRESENT MULTIBOOT_MMAP_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+44]
	
	ret

mboot_memmapPtr:
	CHECK_IF_PRESENT MULTIBOOT_MMAP_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+48]

	ret

mboot_drivesLen:
	CHECK_IF_PRESENT MULTIBOOT_DRIVES_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+52]

	ret

mboot_drivesPtr:
	CHECK_IF_PRESENT MULTIBOOT_DRIVES_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+56]

	ret

mboot_configTable:
	CHECK_IF_PRESENT MULTIBOOT_CONFIGTAB_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+60]

	ret

mboot_apmTable:
	CHECK_IF_PRESENT MULTIBOOT_APMTAB_PRESENT, __LINE__

	mov edx, dword [MULTIBOOT_INFO]
	mov eax, dword [edx+64]

	ret
