


#include <stdint.h>

// serial port (MU IO)
#define MU_IO_BASE 0x3F215040  // 0xFE215004 for Pi 4

// Function to write a character to the serial port
void putc(int data) {
    // Wait until the transmit FIFO is not full
    while (*(volatile uint32_t *)(MU_IO_BASE + 0x18) & (1 << 5)) {
    }

    // Write the character to the transmit register
    *(volatile uint32_t *)(MU_IO_BASE) = (uint32_t)data;
}

// Print the current execution level
void print_execution_level() {
    // Assuming getEL() returns the current execution level
    extern int getEL();  // Forward declaration of getEL
    esp_printf(putc, "Current Execution Level is %d\r\n", getEL());
}
