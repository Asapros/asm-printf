strlen:
    xor rax, rax

.for:
    cmp byte [rdi], 0
    je .done

    inc rax
    inc rdi
    jmp .for
    jmp a

.done:
    ret
