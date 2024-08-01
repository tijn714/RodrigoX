# IDT
.global load_idt
load_idt:
    movl 4(%esp), %eax  # get idt pointer
    lidt (%eax)         # load idt
    ret
    