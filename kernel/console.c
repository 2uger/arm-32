// Console module will refer to output
// Since we writing it for embedded aims
// It's all will took output to UART

#include "defs.h"

void consoleinit(void) {
    uart_init();
}

void printf(void) {
}
