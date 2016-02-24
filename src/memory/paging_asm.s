[GLOBAL paging_setDirectory]
[GLOBAL paging_enablePAE]
[GLOBAL paging_enable]
[GLOBAL PAGE_DIRECTORY]
    
SECTION .bss align=4096

PAGE_DIRECTORY:  resd 1024
    
SECTION .text
    
PAGING_ENABLE:          equ 0x80000000
PAE_ENABLE: 		equ 0x20
    
paging_setDirectory:            ;esp+4 - directory
    mov eax, [esp+4]
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
