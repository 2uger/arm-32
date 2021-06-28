// Fake UART just for testing
// Will setup it in normal mode when
// Test on real hardware
#include "stdint.h"

static volatile unsigned int * const UART_DR = (unsigned int *)0x4000c000;

void uart_init(void) {
}

void uart_sendchar(const char c) {
    *UART_DR = c;
}


