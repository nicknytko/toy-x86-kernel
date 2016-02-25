[GLOBAL paging_setDirectory]
[GLOBAL paging_enablePAE]
[GLOBAL paging_enable]
[GLOBAL paging_initHigherHalf]
[GLOBAL PAGE_DIRECTORY]
[GLOBAL PAGE_TABLE_KERNEL]
[EXTERN kmain]
[EXTERN stack]    
    
SECTION .data
align 4096

PAGE_DIRECTORY:  times 1024 dd 0
PAGE_TABLE_KERNEL:   times 1024 dd 0
    
SECTION .text
    
PAGING_ENABLE:          equ 0x80000000
PAE_ENABLE: 		equ 0x20
    
paging_setDirectory:            ;esp+4 - directory
    mov eax, [esp+4]
    sub eax, 0xC0000000
    and eax, 0xFFFFF000         ; Set the upper 20 bits of CR3 to the page directory
    mov cr3, eax                
    ret

paging_enablePAE:
    mov eax, cr4
    or eax, PAGING_ENABLE       ; Enable PAE by setting the 5th bit in CR4
    mov cr4, eax
    ret
    
paging_enable: 
    mov eax, cr0
    or eax, PAGING_ENABLE       ; Enable paging by setting the 32nd bit in CR0
    mov cr0, eax
    ret

paging_initHigherHalf:          ;esp+4 - kernel offset
    mov eax, _paging_initHigherHalf_jump
    jmp eax                     ;jump to new location

_paging_initHigherHalf_jump:    
    
    mov dword [PAGE_DIRECTORY], 0 ;clear old identity mapping

    mov esp, stack
    jmp kmain
    
    mov eax, [esp]
    add eax, [esp+4]
    mov [esp], eax              ;hack to fix return location
    ret
