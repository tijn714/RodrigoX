#include "timer.h"
#include "idt.h"
#include "io_ports.h"
#include "isr.h"
#include "memory.h"

uint32_t g_ticks = 0;
uint16_t g_freq_hz = 0;
uint32_t u_ticks = 0; // universal ticks (since boot)

void timer_set_frequency(uint16_t f) {
    g_freq_hz = f;
    uint16_t divisor = TIMER_INPUT_CLOCK_FREQUENCY / f;
    // set Mode 3 - Square Wave Mode
    outportb(TIMER_COMMAND_PORT, 0b00110110);
    // set low byte
    outportb(TIMER_CHANNEL_0_DATA_PORT, divisor & 0xFF);
    // set high byte
    outportb(TIMER_CHANNEL_0_DATA_PORT, (divisor >> 8) & 0xFF);
}


void timer_handler(REGISTERS* r) {
    g_ticks++;
    u_ticks++;
}

void timer_init() {
    timer_set_frequency(100);
    isr_register_interrupt_handler(IRQ_BASE, timer_handler);
}

void sleep(int ms) {
    uint32_t start = u_ticks;
    while (u_ticks < start + ms) {

    }
}

void get_date_time(DATE_TIME *dt) {
    // read RTC registers
    outportb(0x70, 0x00);
    dt->second = inportb(0x71);
    outportb(0x70, 0x02);
    dt->minute = inportb(0x71);
    outportb(0x70, 0x04);
    dt->hour = inportb(0x71);
    outportb(0x70, 0x07);
    dt->day = inportb(0x71);
    outportb(0x70, 0x08);
    dt->month = inportb(0x71);
    outportb(0x70, 0x09);
    dt->year = inportb(0x71);

    // convert BCD to binary
    dt->second = (dt->second & 0x0F) + ((dt->second / 16) * 10);
    dt->minute = (dt->minute & 0x0F) + ((dt->minute / 16) * 10);
    dt->hour = (dt->hour & 0x0F) + (((dt->hour & 0x70) / 16) * 10);
    dt->day = (dt->day & 0x0F) + ((dt->day / 16) * 10);
    dt->month = (dt->month & 0x0F) + ((dt->month / 16) * 10);
    dt->year = (dt->year & 0x0F) + ((dt->year / 16) * 10);

    // convert 12-hour clock to 24-hour clock
    if (!(dt->hour & 0x80)) {
        if ((dt->hour & 0x70) == 0x70) {
            dt->hour = 0x10 | (dt->hour & 0x0F);
        }
    } else {
        if ((dt->hour & 0x70) != 0x70) {
            dt->hour = 0x20 | (dt->hour & 0x0F);
        }
    }


    // als het uur 24 is, dan is het 00:00
    if (dt->hour == 24) {
        dt->hour = 0;
    }

    // convert year to 4-digit format
    dt->year += 2000;


}