[GLOBAL paging_setDirectory]

PAGING_ENABLE:          equ 0x80000000
        
paging_setDirectory:            ;esp+4 - directory
    mov eax, [esp+4]
    mov cr3, eax
    mov eax, cr0
    or eax, PAGING_ENABLE
    mov eax, cr0
