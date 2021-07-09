// Console module will refer to output
// Since we writing it for embedded aims
// It's all will took output to UART

#include <cstdarg.h>

#include "defs.h"

void consoleinit(void) {
    uart_init();
}

void putchar(const char * s) {
    uart_sendchar(*s);
}

void printf(const char * format, ...) {
    va_list ap;
    
    va_start(ap, format);
    char * c;
    c = format;
    while (*c != '\0') {
        if (*c != '%') {
            putchar(c);
            continue;
        }
        switch(*c) {
        case ('d'):
            printint(va_arg(ap, uint32_t), 10);
            break;
        case ('x'):
            printint(va_arg(ap, uint32_t), 16);
            break;
        case ('p'):
            // TODO: check if we need to get a pointer uint32_t *
            printptr(va_arg(ap, uint32_t));
            break;
        case ('s'):
            putchar(va_arg(ap, char));
            break;
        case ('%'):
            putchar(*c);
            break;
        case default:
            putchar(*c);
            break;
        }
    }
    
}


void printptr(uint32_t ) {

}

static char nums[] = "0123456789abcdef";

void printint(uint32_t value, uint32_t base) {
    char buf[16];
    uint32_t x;
    x = value;
    int i = 0;
    while (value > 0) {
        buf[i] = nums[x % base];
        x /= base;
        i++;
    }
    putchar('h');
    while (i-- > 0)
        putchar(buf[i]);
}
