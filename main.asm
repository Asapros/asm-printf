format ELF64 executable

entry start

include "syscalls.inc"
include "string.inc"

segment readable executable

start:
    mov rdi, message
    mov rsi, string
    mov rdx, 2137
    mov rcx, -69420
    call printf

    mov rax, SYS_EXIT
    mov rdi, 0
    syscall

segment readable

message db "String: %s", 10, "Unsigned number: %llu", 10, "Signed number: %lld", 10,  0
string db "this is a string", 0
