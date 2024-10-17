
// char glbl[128];
// char huge_array[8192];

#include "mmu.h"

#include <stdint.h>

extern char __bss_start;
extern char __bss_end;

void clear_bss() {
    char *ptr = &__bss_start;
    while (ptr < &__bss_end) {
        *ptr = 0;
        ptr++;
    }
}

unsigned long get_timer_count() {
    unsigned long *timer_count_register = (unsigned long *)0x3f003004;
    return *timer_count_register;
}

void wait_for_ms(unsigned long ms) {
    unsigned long start = get_timer_count();
    unsigned long delay = ms * 1000; // Convert ms to microseconds
    while ((get_timer_count() - start) < delay) {
        // Busy-wait
    }
}


void delay() {
    wait_for_ms(0); // Calls wait_for_ms with 0
}



void kernel_main() {
    // Clear the BSS segment
    clear_bss();

    // Get the timer count
    unsigned long timer_count = get_timer_count();

    // Set breakpoint with gdb

    // Wait for 1 ms
    wait_for_ms(1);

    // Check again
    timer_count = get_timer_count();

    // Set breakpoint

    // Loop forever
    while (1) {
        delay();
    }

    if (mmu_on() != 0){

        while (1);

    }


}

