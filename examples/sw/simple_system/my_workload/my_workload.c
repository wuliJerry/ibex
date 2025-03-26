#include <stdint.h>

#define TIMER_BASE 0x80000000
#define TIMER_CTRL *(volatile uint32_t *)(TIMER_BASE + 0x0)

void delay(int cycles) {
    for (volatile int i = 0; i < cycles; i++);
}

int main() {
    while (1) {
        TIMER_CTRL = 1;  // "Turn on LED"
        delay(100000);
        TIMER_CTRL = 0;  // "Turn off LED"
        delay(100000);

    }
    return 0;
}
