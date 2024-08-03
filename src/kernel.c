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
    timer_init();
    keyboard_init();
    init_screen();

    int i = 0;

    kprint("Welcome to RodrigoX!\n");
    kprint("Screen: %dx%d\n\n", SCREEN_WIDTH, SCREEN_HEIGHT);


    for (;;) {
        kprint("\rUptime: %d seconds", i);
        i++;
        sleep(100);
    }
} 