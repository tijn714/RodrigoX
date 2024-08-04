#include "idt.h"
#include "io_ports.h"
#include "isr.h"
#include "memory.h"
#include "timer.h"

uint32_t ticks;

static void timer_callback(REGISTERS *reg) {
    ticks++;
}

void timer_set_frequency(uint32_t frequency) {
    isr_register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = TIMER_INPUT_CLOCK_FREQUENCY / frequency;

    outportb(TIMER_COMMAND_PORT, 0x36);

    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    outportb(TIMER_CHANNEL_0_DATA_PORT, low);
    outportb(TIMER_CHANNEL_0_DATA_PORT, high);
}

void sleep(uint32_t ms) {
    uint32_t start = ticks;
    while (ticks < start + ms);
}

void timer_init() {
    timer_set_frequency(100);
}