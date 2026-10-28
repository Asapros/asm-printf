malloc:
    mov rsi, rdi

    xor rdi, rdi
    mov rdx, 3
    mov r10, 0x22
    mov r8, -1
    xor r9, r9
    mov eax, 9

    syscall
    ret

free:
    mov eax, 11

    syscall
    ret
