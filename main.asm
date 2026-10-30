format ELF64 executable

entry start

include "memory.inc"
include "syscalls.inc"
include "string.inc"

segment readable executable

start:
    mov rdi, message
    mov rsi, greeting
    mov rdx, 2137
    call printf

    mov rax, SYS_EXIT
    mov rdi, 0
    syscall

segment readable

message db "%s, %lld!", 10, 0
greeting db "Hello", 0
recipient db "World", 0
