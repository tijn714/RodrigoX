#include "types.h"
#include "memory.h"
#include "gdt.h"
#include "isr.h"
#include "idt.h"
#include "io_ports.h"
#include "timer.h"
#include "keyboard.h"
#include "screen.h"

void kmain() {
    gdt_init();
    idt_init();
    keyboard_init();
    timer_init();
    init_screen();

    uint32_t uptime;

    kprint("Welcome to RodrigoX!\n");
    kprint("Screen: %dx%d\n\n ", SCREEN_WIDTH, SCREEN_HEIGHT);

    for (;;) {
        kprint("\rUptime: %d seconds", uptime);
        sleep(100);
        uptime++;
    }
} 