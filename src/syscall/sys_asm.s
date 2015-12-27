[GLOBAL syscall_stub]
[GLOBAL syscall_test]
[EXTERN sys_exit]
[EXTERN sys_fork]
[EXTERN sys_kill]
[EXTERN sys_getpid]
[EXTERN sys_read]
[EXTERN sys_write]
[EXTERN sys_open]
[EXTERN sys_close]
[EXTERN sys_execve]
[EXTERN sys_fstat]
[EXTERN sys_stat]
[EXTERN sys_link]
[EXTERN sys_unlink]
[EXTERN sys_lseek]
[EXTERN sys_sbrk]
[EXTERN sys_times]
[EXTERN sys_wait]

syscall_table:
	dd sys_exit
	dd sys_fork
	dd sys_kill
	dd sys_getpid
	dd sys_read
	dd sys_write
	dd sys_open
	dd sys_close
	dd sys_execve
	dd sys_fstat
	dd sys_stat
	dd sys_link
	dd sys_unlink
	dd sys_lseek
	dd sys_sbrk
	dd sys_times
	dd sys_wait

syscall_test:	
	mov eax, [esp+4]
	mov ebx, [esp+8]
	mov ecx, [esp+12]
	mov edx, [esp+16]

	int 0x30
	
	ret
	
syscall_stub:
	cli

	cmp eax, 0x1
	jl _syscall_fail_check

	cmp eax, 0x11
	jg _syscall_fail_check

	push edx
	push ecx
	push ebx

	dec eax

	call dword [eax*4 + syscall_table]

_syscall_fail_check:	
	
	add esp, 12
	iret
