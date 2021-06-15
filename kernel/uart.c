// Fake UART just for testing
// Will setup it in normal mode when
// Test on real hardware

#define UART_DR (uint32_t *(0x4000c000))

void uart_init(void) {
}

void uart_sendchar(const char c) {
    *UART_DR = c;
}


