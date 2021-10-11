// Console module will refer to output
// Since we writing it for embedded aims
// It's all will took output to UART

#include <stdarg.h>
#include <stdint.h>

#include "defs.h"

void
consoleinit(void)
{
    uart_init();
}

void
pputchar(const char c)
{
    uart_sendchar(c);
}

static char nums[] = "0123456789abcdef";

void
printint(int32_t value, uint8_t base, uint8_t sign)
{
    if (value == 0) {
        pputchar('0');
        return;
    }
    char buf[16];
    int32_t x;

    if (sign && value < 0)
        x = value * (-1);
    else {
        sign = 0;
        x = value;
    }

    uint32_t i = 0;
    while (x > 0) {
        buf[i] = nums[x % base];
        x /= base;
        i++;
    }

    if (sign)
        buf[i++] = '-';

    switch (base) {
        case (8): 
            pputchar('0');
            pputchar('o');
            break;
    }
    while (i-- > 0)
        pputchar(buf[i]);
}

void
printptr(uint32_t p_addr)
{
    pputchar('0');
    pputchar('x');
    printint(p_addr, 16, 1);
}


void
kprintf(char * format, ...)
{
    va_list ap;
    va_start(ap, format);
    char * str;
    char * c;
    for(c = format; *c != '\0'; c++){
        if (*c != '%') {
            pputchar(*c);
            continue;
        }
        c++;
        switch(*c) {
        // decimal
        case ('d'):
            printint(va_arg(ap, uint32_t), 10, 1);
            break;
        // hex
        case ('x'):
            printint(va_arg(ap, uint32_t), 16, 1);
            break;
        // address
        case ('p'):
            // TODO: check if we need to get a pointer uint32_t *
            printptr(va_arg(ap, uint32_t));
            break;
        // character
        case ('c'):
            pputchar(va_arg(ap, uint32_t));
            break;
        // string
        case ('s'):
            str = va_arg(ap, uint32_t);
            while (*str != '\0') {
                pputchar(*str++);
            }
            break;
        case ('%'):
            pputchar(*c);
            break;
        default:
            pputchar(*c);
            break;
        }
    }
    va_end(format);
}
