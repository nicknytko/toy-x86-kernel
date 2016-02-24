[GLOBAL cpuid_getVendor]
[GLOBAL cpuid_getECXFeatures]
[GLOBAL cpuid_getEDXFeatures]
[GLOBAL cpuid_existsECX]
[GLOBAL cpuid_existsEDX]    
    
SECTION .bss

CPUID_STR: resb 13

SECTION .text

cpuid_getVendor:
    xor eax, eax
    
    cpuid
    
    mov dword [CPUID_STR], ebx
    mov dword [CPUID_STR+4], edx
    mov dword [CPUID_STR+8], ecx
    mov byte [CPUID_STR+12], 0

    mov eax, CPUID_STR
    ret

cpuid_getECXFeatures:
    mov eax, 1
    cpuid
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
    jz _cpuid_existsECX_end     ; if not, return 0
    
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
