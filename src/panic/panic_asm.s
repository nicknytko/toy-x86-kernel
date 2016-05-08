[EXTERN kpanic_c]
[EXTERN int_cli]
[GLOBAL kpanic]
    
kpanic:
    
    pushad                      ; push all registers so we can print them in our panic screen
    
    mov eax, [esp+36]           ; push error string
    push eax
    
    call kpanic_c
    add esp, 36

    call int_cli                ; disable interrupts
    
_kpanic_loop:
    hlt                         ; infinitely loop
    jmp _kpanic_loop
