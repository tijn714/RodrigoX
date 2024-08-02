#include "system.h"
#include "screen.h"

void panic(char *msg, REGISTERS reg) {
    // FOr now halt the system
    asm volatile("cli");
    asm volatile("hlt");
}