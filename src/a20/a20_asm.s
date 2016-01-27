[GLOBAL a20_enable_bios]
[GLOBAL a20_enable_fast]
[EXTERN ps2_wait_read]
[EXTERN ps2_wait_write]
        
PS2_RW          equ 0x60
PS2_STATUS      equ 0x64
PS2_COMMAND     equ 0x64

a20_enable_bios:
    ;; we have to go back to 16-bit mode in order to do bios calls

    [BITS 16]
    mov ax, 0x2401
    int 0x15
    [BITS 32]
    
    ;; if there is an error, CF will be set
        
    jc _a20_enable_bios_fail
    mov eax, 1
    ret

_a20_enable_bios_fail:
    xor eax, eax
    ret

a20_enable_fast:
    in al, 0x92
    or al, 0x2
    out 0x92, al
        
    ret
