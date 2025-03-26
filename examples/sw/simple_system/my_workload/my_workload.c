#include <stdint.h>
#define SIM_CTRL_ADDR *(volatile uint32_t *)(0x80002008)
int main() {
    for (int i = 0; i < 200; i++) {  // Double the loop
        // Dummy work
        volatile int x = i;
    }
    SIM_CTRL_ADDR = 1;
    return 0;
}