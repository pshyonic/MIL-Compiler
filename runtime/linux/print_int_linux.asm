global print_int
section .text

print_int:
    XOR rcx, 0
    MOV rbx, 10
    XOR r8d, r8d
    CMP rax, 0
    JE .print_zero
    JL .negative
    JMP .loop1

    .negative:
        NEG rax
        INC rcx
        MOV r8d, 1
        

    .loop1:
        CQO
        IDIV rbx
        ADD rdx, '0'
        SUB rsp, 1
        MOV byte [rsp], dl
        INC rcx
        cmp rax, 0
        JNE .loop1

        JMP .print_regular

    .print_zero:
        SUB rsp, 1
        MOV byte [rsp], '0'
        INC rcx

    .print_regular:

        cmp r8d, 1
        JNE .print_call
        SUB rsp, 1
        MOV byte [rsp], '-'

    .print_call:
        MOV r9, rcx
        MOV rax, 1
        MOV rdi, 1
        MOV rsi, rsp
        MOV rdx, rcx
        SYSCALL

    ADD rsp, r9

    ret
