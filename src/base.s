[GLOBAL halt]
[GLOBAL inb]
[GLOBAL inw]
[GLOBAL outb]
[GLOBAL set_dword]
[GLOBAL set_word]
[GLOBAL set_byte]
[GLOBAL get_dword]
[GLOBAL get_word]
[GLOBAL get_byte]
[GLOBAL stack]    

SECTION .bss
align 0x20

STACKSIZE: equ 0x4000
    
_stack: resb STACKSIZE
stack:  equ _stack + STACKSIZE
    
SECTION .text
    
halt:
    hlt                         ;halt (and catch fire)
    jmp halt
    
inb:                            ;esp+4 - port
    mov edx, [esp+4]
    in al, dx
    ret

inw:                            ;esp+4 - port
    mov edx, [esp+4]
    in ax, dx
    ret
        
outb:                           ;esp+4 - port, esp+8 - value
    mov edx, [esp+4]
    mov eax, [esp+8]
    out dx, al
    ret

set_dword:                      ;esp+4 - address, esp+8 - value
    mov eax, [esp+4]
    mov edx, [esp+8]
    mov dword [eax], edx
    ret

set_word:                       ;esp+4 - address, esp+8 - value
    mov eax, [esp+4]
    mov edx, [esp+8]
    mov word [eax], dx
    ret

set_byte:                       ;esp+4 - address, esp+8 - value
    mov eax, [esp+4]
    mov edx, [esp+8]
    mov byte [eax], dl
    ret

get_dword:                      ;esp+4 - address
    mov edx, [esp+4]
    mov eax, dword [edx]
    ret

get_word:                       ;esp+4 - address
    mov edx, [esp+4]
    mov ax, word [edx]
    ret

get_byte:                       ;esp+4 - address
    mov edx, [esp+4]
    mov al, byte [edx]
    ret
