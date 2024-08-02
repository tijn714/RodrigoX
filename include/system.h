#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"
#include "isr.h"

void panic(char *msg, REGISTERS reg);

#endif // SYSTEM_H