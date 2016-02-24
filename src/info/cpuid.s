[GLOBAL cpuid_getVendor]
[GLOBAL cpuid_getECXFeatures]
[GLOBAL cpuid_getEDXFeatures]
[GLOBAL cpuid_existsECX]
[GLOBAL cpuid_existsEDX]    
[GLOBAL cpuid_getStepping]
[GLOBAL cpuid_getModel]
[GLOBAL cpuid_getFamily]
[GLOBAL cpuid_getType]
    
SECTION .bss

CPUID_STR: resb 13

SECTION .text

cpuid_getVendor:
    xor eax, eax
    
    cpuid                       ; eax = 0, cpuid returns the vendor string in ebx, edx, and ecx
    
    mov dword [CPUID_STR], ebx
    mov dword [CPUID_STR+4], edx
    mov dword [CPUID_STR+8], ecx
    mov byte [CPUID_STR+12], 0

    mov eax, CPUID_STR
    ret

cpuid_getECXFeatures:
    mov eax, 1
    cpuid                       ; eax = 1, cpuid returns features in ecx and edx
    mov eax, ecx
    ret

cpuid_getEDXFeatures:
    mov eax, 1
    cpuid
    mov eax, edx
    ret

cpuid_existsECX:
    mov eax, 1
    cpuid
    mov eax, ecx
    
    test eax, [esp+4]           ; bitwise and to see if the feature bit is set
    jz _cpuid_existsECX_end     ; if not zero flag will be set so return 0
    
    mov eax, 1
    ret
_cpuid_existsECX_end:
    xor eax, eax
    ret

cpuid_existsEDX:
    mov eax, 1
    cpuid
    mov eax, edx
    
    test eax, [esp+4]
    jz _cpuid_existsEDX_end
    
    mov eax, 1
    ret
_cpuid_existsEDX_end:
    xor eax, eax
    ret

cpuid_getStepping:
    mov eax, 1
    cpuid
    and eax, 0xF
    ret

cpuid_getModel:
    mov eax, 1
    cpuid
    
    mov ebx, eax
    and eax, 0xF0               ; Get model from bits 7-4
    shr eax, 4
    
    xchg eax, ebx
    and eax, 0xF0000            ; Get extended model from bits 19-16
    shr eax, 0xC                ; Shift right 16 bits and left 4
    add eax, ebx                ; Add together
    
    ret

cpuid_getFamily:
    mov eax, 1
    cpuid

    mov ebx, eax
    and eax, 0xF00              ; Get family from bits 11-8
    shr eax, 8

    xchg eax, ebx
    and eax, 0xF00000           ; Get extended family bits
    shr eax, 0x14               ; Shift right 20 bits
    add eax, ebx                ; Add together and return
    
    ret

cpuid_getType:
    mov eax, 1
    cpuid

    and eax, 0x3000             ; Get type from bits 13-12
    shr eax, 0xC
    
    ret
