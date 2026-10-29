format ELF64 executable

entry start

include "memory.inc"
include "syscalls.inc"
include "string.inc"

segment readable executable

; Parameter order: rdi, rsi, rdx, rcx, r8, r9

start:
    mov rdi, message
    mov rsi, greeting
    mov rdx, 213769
    call printf

    mov rax, SYS_EXIT
    mov rdi, 0
    syscall

segment readable

message db "%s, %d!", 10, 0
greeting db "Hello", 0
recipient db "World", 0
