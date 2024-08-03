.section .text
.global _start
_start:
    movl $system_stack, %esp
    jmp _stublet

.align 4
mboot:
    # MULTIBOOT constants
    .equ MULTIBOOT_PAGE_ALIGN, 1<<0
    .equ MULTIBOOT_MEM_INFO, 1<<1
    .equ MULTIBOOT_AOUT_KLUDGE, 1<<16
    .equ MULTIBOOT_MAGIC_NUM, 0x1BADB002
    .equ MULTIBOOT_HEADER_FLAGS, MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEM_INFO | MULTIBOOT_AOUT_KLUDGE
    .equ MULTIBOOT_CHECKSUM, -(MULTIBOOT_MAGIC_NUM + MULTIBOOT_HEADER_FLAGS)

    .extern code, bss, end

    # GRUB MULTIBOOT Header & Boot Signature
    .long MULTIBOOT_MAGIC_NUM
    .long MULTIBOOT_HEADER_FLAGS
    .long MULTIBOOT_CHECKSUM

    .long mboot
    .long code
    .long bss
    .long end
    .long _start

_stublet:
    .extern kmain
    call kmain
    jmp .

.section .bss
    .space 8192    # 8MB Memory Reserved
system_stack: