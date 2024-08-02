#include "types.h"
#include "memory.h"
#include "gdt.h"
#include "isr.h"
#include "idt.h"
#include "io_ports.h"
#include "timer.h"
#include "keyboard.h"
#include "screen.h"

void kmain(uint32_t magic) {
    gdt_init();
    idt_init();
    timer_init();
    keyboard_init();
    init_screen();

    int i = 0;

    for (;;) {
        kprint("\r Hello, World! %d", i);
        i++;
        sleep(100);
    }
} 