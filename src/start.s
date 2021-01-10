.intel_syntax noprefix
.ident "GCC: (GNU) 9.2.0"

.global _start
_start:
    call _entry
    mov rdi, rax
    call exit

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
