# GDT
.global load_gdt
load_gdt:
    movl 4(%esp), %eax  # get gdt pointer
    lgdt (%eax)         # load gdt

    movw $0x10, %ax     # kernel data segment
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss

    cli                 # clear interrupts
    movl %cr0, %eax     # set bit 0 in cr0 to enter protected mode
    orl $1, %eax
    movl %eax, %cr0

    ljmp $0x08, $far_jump  # jump to far with code data segment
far_jump:
    ret
    