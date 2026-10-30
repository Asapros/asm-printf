segment readable executable

memcpy: ; destination, source, size
    cmp rdx, 0
    je .done
    
    mov cl, byte [rsi]
    mov [rdi], cl

    inc rdi
    inc rsi
    dec rdx

    jmp memcpy
.done:
    ret

strcpy: ; destination, source
    push rdi
    push rsi

    mov rdi, rsi
    call strlen

    mov rdx, rax
    pop rsi
    pop rdi
    call memcpy

    ret

memchr: ; pointer, character, max length
    mov rax, rdi
.for:
    cmp byte [rax], sil
    je .found
    
    inc rax
    dec rdx
    jz .not_found

    jmp .for
.not_found:
    mov rax, 0

    ret
.found:
    ret

strchr: ; pointer, character
    push rdi
    push rsi

    call strlen

    pop rsi
    pop rdi
    mov rdx, rax
    call memchr

    ret

rawmemchr: ; pointer, character
    mov rdx, -1
    call memchr

    ret

strlen: ; pointer
    push rdi

    mov sil, 0
    call rawmemchr

    pop rdi
    sub rax, rdi

    ret

fwrite: ; pointer, length, stream
    mov rcx, rsi
    mov rsi, rdi
    mov rdi, rdx
    mov rdx, rcx
    mov rax, SYS_WRITE
    syscall

    ret

fputs: ; pointer, stream
    push rdi
    push rsi
    call strlen

    pop rdx
    pop rdi
    mov rsi, rax
    call fwrite

    ret

printf: ; pointer, ...
    mov rbp, rsp
    
    push r9
    push r8
    push rcx
    push rdx
    push rsi
.repeat:
    push rdi
    mov rsi, "%"
    call strchr

    pop rdi
    cmp rax, 0
    je .rest

    mov rsi, rax
    sub rsi, rdi
    mov rdx, STDOUT
    push rdi
    push rsi
    call fwrite

    pop rsi
    pop rdi
    add rdi, rsi
    inc rdi

    cmp byte [rdi], "s"
    je .string

    cmp byte [rdi], "l"
    jne .not_number
    cmp byte [rdi+1], "l"
    jne .not_number
    cmp byte [rdi+2], "u"
    je .number_unsigned
    cmp byte [rdi+2], "d"
    je .number_signed
.not_number:
    cmp byte [rdi], "%"
    je .escape

    jmp .repeat
.number_signed:
    pop rax
    xor r8, r8 

    cmp rax, 0
    jge .number

    neg rax
    mov r8, 1
    jmp .number
.number_unsigned:
    pop rax
.number:
    mov rsi, printf_buffer + PRINTF_BUFFER_SIZE - 1
    mov [rsi], byte 0
.digit:
    xor rdx, rdx
    mov rcx, 10
    div rcx
    
    dec rsi
    add dl, "0"
    mov [rsi], dl

    cmp rax, 0
    je .flush

    jmp .digit
.flush:
    cmp r8, 0
    je .flush_unsigned
    dec rsi
    mov [rsi], byte "-"
.flush_unsigned:
    push rdi
    
    mov rdi, rsi
    mov rsi, STDOUT
    call fputs
    pop rdi
    add rdi, 3

    jmp .repeat
.escape:
    mov rsi, 1
    mov rdx, STDOUT
    push rdi
    call fwrite
    pop rdi
    inc rdi
    jmp .repeat
.string:
    pop rsi
    push rdi

    mov rdi, rsi
    mov rsi, STDOUT
    call fputs 

    pop rdi
    inc rdi

    jmp .repeat
.rest:
    mov rsi, STDOUT
    call fputs
.done:
    mov rsp, rbp
    ret

segment readable writable

PRINTF_BUFFER_SIZE = 24
printf_buffer rb PRINTF_BUFFER_SIZE
