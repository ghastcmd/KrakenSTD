.intel_syntax noprefix
.ident "GCC: (GNU) 9.2.0"

.global _start
_start:
    call _entry
    mov rdi, rax
    call exit

.macro scall name code
.global \name
\name:
    mov rax, \code
    mov r10, rcx
    syscall
    ret
.endm

#ifdef __linux__

scall read 0
scall write 1
scall open 2
scall close 3
scall exit 60

#else

scall NtWriteFile 0x8
scall NtClose 0xf
scall NtOpenFile 0x33
scall NtCreateFile 0x55
scall NtTerminateProcess 0x2c

#endif
