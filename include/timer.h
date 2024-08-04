#ifndef TIMER_H
#define TIMER_H

#include "types.h"

#define TIMER_INPUT_CLOCK_FREQUENCY     1193180
#define TIMER_CHANNEL_0_DATA_PORT       0x40
#define TIMER_CHANNEL_1_DATA_PORT       0x41
#define TIMER_CHANNEL_2_DATA_PORT       0x42
#define TIMER_COMMAND_PORT              0x43

#define TIMER_FREQUENCY                 100
#define IRQ0                            32


extern uint32_t ticks;

void timer_init();
void timer_set_frequency(uint32_t frequency);
void sleep(uint32_t ms);

#endif
