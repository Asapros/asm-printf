format ELF64 executable

entry start

include "memory.inc"
include "syscalls.inc"
include "string.inc"

segment readable executable

; rdi rsi rdx rcx r8 r9

start:
    mov rdi, message
    call printf

    mov rax, SYS_EXIT
    mov rdi, 0
    syscall

segment readable

message db "Hello, World!", 10, 0
