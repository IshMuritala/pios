

#ifndef DELAYS_H
#define DELAYS_H

void wait_msec(unsigned int msec) {
    for (unsigned int i = 0; i < msec * 1000; i++) {
        asm volatile("nop");
    }
}

void wait_cycles(unsigned int cycles) {
    for (unsigned int i = 0; i < cycles; i++) {
        asm volatile("nop");
    }
}

#endif
