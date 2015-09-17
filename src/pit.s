[GLOBAL pit_init]
[GLOBAL pit_callback]
[EXTERN irq_loadHandler]
	
	PIT_PORT_CH0         equ 0x40
	PIT_PORT_CH1         equ 0x41
	PIT_PORT_CH2         equ 0x42
	PIT_MODE             equ 0x43

	PIT_INPUT_CLOCK      equ 1193180
	
;; Channel select

	PIT_CHANNEL_0        equ 00000000b
	PIT_CHANNEL_1        equ 10000000b
	PIT_CHANNEL_2        equ 01000000b
	PIT_READBACK         equ 11000000b

;; Channel mode

	PIT_LATCH_COUNT      equ 00000000b
	PIT_ACCESS_LOW       equ 00100000b
	PIT_ACCESS_HIGH      equ 00010000b
	PIT_ACCESS_BOTH      equ 00110000b

;; Operating Mode

	PIT_MODE_0           equ 00000000b
	PIT_MODE_1           equ 00001000b
	PIT_MODE_2           equ 00000100b
	PIT_MODE_3           equ 00001100b
	PIT_MODE_4           equ 00000010b
	PIT_MODE_5           equ 00001010b
	PIT_MODE_2_2         equ 00000110b ;same thing as PIT_MODE_2
	PIT_MODE_3_2         equ 00001110b ;same thing as PIT_MODE_3

;; Config

	PIT_FLAGS            equ (PIT_CHANNEL_0 | PIT_ACCESS_BOTH | PIT_MODE_2_2)

PIT_TICKS: dd 0
	
pit_callback:
	mov ebx, PIT_TICKS
	mov eax, dword [ebx]
	inc eax
	mov dword [ebx], eax
	
	ret
	
pit_init: 			;[esp+4] - frequency in hz
	push 0
	push pit_callback
	call irq_loadHandler

	mov eax, PIT_FLAGS
	out PIT_MODE, al
	
	pop ebx
	pop ecx
	push ebx

	mov eax, PIT_INPUT_CLOCK
	xor edx, edx
	div ecx
	
	mov bl, ah

	out PIT_PORT_CH0, al
	mov al, bl
	out PIT_PORT_CH0, al
	
	ret
