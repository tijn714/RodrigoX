.code32
.section .text.prologue

.global start
start:
    movl $stack, %esp
    andl $-16, %esp
    movl $0xDEADBEEF, %eax
    pushl %esp
    pushl %eax
    cli
    call kmain
    hlt

.section .data
.align 32
stack_begin:
    .fill 0x4000
stack:
