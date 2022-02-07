// Fake UART just for testing
// Will setup it in normal mode when
// Test on real hardware
#include "stdint.h"

static volatile uint32_t * const UART_DR = (uint32_t *)0x4000c000;

void uart_init(void) {
}

void uart_sendchar(char c) {
    *UART_DR = c;
}
