# Exception Handlers
.extern isr_exception_handler
.global exception_0
.global exception_1
.global exception_2
.global exception_3
.global exception_4
.global exception_5
.global exception_6
.global exception_7
.global exception_8
.global exception_9
.global exception_10
.global exception_11
.global exception_12
.global exception_13
.global exception_14
.global exception_15
.global exception_16
.global exception_17
.global exception_18
.global exception_19
.global exception_20
.global exception_21
.global exception_22
.global exception_23
.global exception_24
.global exception_25
.global exception_26
.global exception_27
.global exception_28
.global exception_29
.global exception_30
.global exception_31
.global exception_128

exception_handler:
    pusha                 # push all registers
    movw %ds, %ax
    pushl %eax            # save ds
    
    movw $0x10, %ax       # load kernel data segment
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    call isr_exception_handler

    popl %ebx             # restore kernel data segment
    movw %bx, %ds
    movw %bx, %es
    movw %bx, %fs
    movw %bx, %gs

    popa                # restore all registers
    addl $0x8, %esp      # restore stack for erro no been pushed

    sti                 # re-enable interrupts
    iret


exception_0:
    cli
    pushl $0     # store default err code(0)
    pushl $0          # push exception number index in IDT
    jmp exception_handler

exception_1:
    cli
    pushl $0     # store default err code(0)
    pushl $1          # push exception number index in IDT
    jmp exception_handler

exception_2:
    cli
    pushl $0     # store default err code(0)
    pushl $2          # push exception number index in IDT
    jmp exception_handler

exception_3:
    cli
    pushl $0     # store default err code(0)
    pushl $3          # push exception number index in IDT
    jmp exception_handler

exception_4:
    cli
    pushl $0     # store default err code(0)
    pushl $4          # push exception number index in IDT
    jmp exception_handler

exception_5:
    cli
    pushl $0     # store default err code(0)
    pushl $5          # push exception number index in IDT
    jmp exception_handler

exception_6:
    cli
    pushl $0     # store default err code(0)
    pushl $6          # push exception number index in IDT
    jmp exception_handler

exception_7:
    cli
    pushl $0     # store default err code(0)
    pushl $7          # push exception number index in IDT
    jmp exception_handler

exception_8:
    cli
    pushl $8          # push exception number index in IDT
    jmp exception_handler

exception_9:
    cli
    pushl $0     # store default err code(0)
    pushl $9          # push exception number index in IDT
    jmp exception_handler

exception_10:
    cli
    pushl $10          # push exception number index in IDT
    jmp exception_handler

exception_11:
    cli
    pushl $11          # push exception number index in IDT
    jmp exception_handler

exception_12:
    cli
    pushl $12          # push exception number index in IDT
    jmp exception_handler

exception_13:
    cli
    pushl $13          # push exception number index in IDT
    jmp exception_handler

exception_14:
    cli
    pushl $14          # push exception number index in IDT
    jmp exception_handler

exception_15:
    cli
    pushl $0     # store default err code(0)
    pushl $15          # push exception number index in IDT
    jmp exception_handler

exception_16:
    cli
    pushl $0     # store default err code(0)
    pushl $16          # push exception number index in IDT
    jmp exception_handler

exception_17:
    cli
    pushl $0     # store default err code(0)
    pushl $17          # push exception number index in IDT
    jmp exception_handler

exception_18:
    cli
    pushl $0     # store default err code(0)
    pushl $18          # push exception number index in IDT
    jmp exception_handler

exception_19:
    cli
    pushl $0     # store default err code(0)
    pushl $19          # push exception number index in IDT
    jmp exception_handler

exception_20:
    cli
    pushl $0     # store default err code(0)
    pushl $20          # push exception number index in IDT
    jmp exception_handler

exception_21:
    cli
    pushl $0     # store default err code(0)
    pushl $21          # push exception number index in IDT
    jmp exception_handler

exception_22:
    cli
    pushl $0     # store default err code(0)
    pushl $22          # push exception number index in IDT
    jmp exception_handler

exception_23:
    cli
    pushl $0     # store default err code(0)
    pushl $23          # push exception number index in IDT
    jmp exception_handler

exception_24:
    cli
    pushl $0     # store default err code(0)
    pushl $24          # push exception number index in IDT
    jmp exception_handler

exception_25:
    cli
    pushl $0     # store default err code(0)
    pushl $25          # push exception number index in IDT
    jmp exception_handler

exception_26:
    cli
    pushl $0     # store default err code(0)
    pushl $26          # push exception number index in IDT
    jmp exception_handler

exception_27:
    cli
    pushl $0     # store default err code(0)
    pushl $27          # push exception number index in IDT
    jmp exception_handler


exception_28:
    cli
    pushl $0     # store default err code(0)
    pushl $28          # push exception number index in IDT
    jmp exception_handler

exception_29:
    cli
    pushl $0     # store default err code(0)
    pushl $29          # push exception number index in IDT
    jmp exception_handler

exception_30:
    cli
    pushl $0     # store default err code(0)
    pushl $30          # push exception number index in IDT
    jmp exception_handler

exception_31:
    cli
    pushl $0     # store default err code(0)
    pushl $31          # push exception number index in IDT
    jmp exception_handler

exception_128:
    cli
    pushl $0     # store default err code(0)
    pushl $128          # push exception number index in IDT
    jmp exception_handler


# IRQ Handlers
.extern isr_irq_handler

irq_handler:
    pusha                 # push all registers
    movw %ds, %ax
    pushl %eax              # save ds

    movw $0x10, %ax          # load kernel data segment
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    pushl %esp
    call isr_irq_handler
    popl %esp

    popl %ebx                # restore kernel data segment
    movw %bx, %ds
    movw %bx, %es
    movw %bx, %fs
    movw %bx, %gs

    popa                # restore all registers
    addl $0x8, %esp        # restore stack for error no been pushed

    sti                 # re-enable interrupts
    iret


.macro IRQ, num, vec
  .global irq_\num
  irq_\num:
    cli
    pushl $0
    pushl $\vec
    jmp irq_handler
.endm


IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47
