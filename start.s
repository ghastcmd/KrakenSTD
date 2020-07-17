.intel_syntax noprefix
.ident "GCC: (GNU) 9.2.0"

.global WinMain
WinMain:
    ret

.global _start
_start:
    xor rbx, rbx
    pop rdi
    mov rsi, rsp
    call _entry
    mov rdi, rax

    call get_os
    cmp rax, 0
    je _win_ret
    
    call exit
    _win_ret:
    ret

_syscall:
    mov r10, rcx
    syscall
    ret

.macro scall name code
.global \name
\name:
    mov rax, \code
    jmp _syscall
.endm

scall read 0
scall write 1
scall open 2
scall close 3
scall exit 60
