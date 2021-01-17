.intel_syntax noprefix
.ident "GCC: (GNU) 9.2.0"

.macro scall name op
.global \name
\name:
    mov r10, rcx
    mov rax, \op
    syscall
    ret
.endm

scall NtWriteFileP 0x8
scall NtCreateFileP 0x55
scall NtQueryPerformanceCounter 0x31

.global normal_func
normal_func:
    push rbp
    mov rbp, rsp 
    sub rsp, 0x20

    mov r10, rcx
    mov rax, 0x31
    syscall    

    add rsp, 0x20
    mov rsp, rbp
    pop rbp
    ret
