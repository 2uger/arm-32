// Console module will refer to output
// Since we writing it for embedded aims
// It's all will took output to UART

#include <stdarg.h>

#include "defs.h"

void consoleinit(void) {
    uart_init();
}

void pputchar(const char c) {
    uart_sendchar(c);
}

void printf(const char * format, ...) {
    va_list ap;
    
    va_start(ap, format);
    char * str;
    for (const char * c = format; *c != '\0'; c++) {
        if (*c != '%') {
            putchar(*c);
            continue;
        }
        c++;
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
        case ('c'):
            pputchar(va_arg(ap, uint32_t));
        case ('s'):
            str = va_arg(ap, uint32_t);
            while (*str != '\0') {
                pputchar(*str++);
            }
            break;
        case ('%'):
            pputchar(*c);
            break;
        case default:
            pputchar(*c);
            break;
        }
    }
}


void printptr(uint32_t p_addr) {
    printint(p_addr, 16);
}

static char nums[] = "0123456789abcdef";

void printint(uint32_t value, uint32_t base) {
    char buf[16];
    uint32_t x;
    x = value;
    uint32_t i = 0;
    while (x > 0) {
        buf[i] = nums[x % base];
        x /= base;
        i++;
    }
    switch (base) {
        case (8): 
            pputchar('0');
            pputchar('o');
            break;
        case (16):
            pputchar('0');
            pputchar('x');
            break;
    }
    while (i-- > 0)
        pputchar(buf[i]);
}
