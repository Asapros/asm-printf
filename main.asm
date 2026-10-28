format ELF64 executable

entry start

segment readable executable

include "string.inc"
include "memory.inc"
include "syscalls.inc"

start:
    mov rdi, message
    call strlen
    
    mov rdx, rax
    mov rsi, message
    mov rdi, 1 ; stdout
    mov rax, 1 ; write
    syscall

    mov rdi, 16
    call malloc

    mov rdi, rax
    mov rsi, 16
    call free


    mov eax, 60
    mov edi, 0
    syscall

segment readable

message db "Hello, World", 0, "abb"
