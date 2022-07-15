// Console module will refer to output
// Since we writing it for embedded aims
// It's all will took output to UART

#include <stdarg.h>
#include <stdint.h>

#include "defs.h"

static volatile uint32_t * const UART_DR = (uint32_t *)0x4000c000;
static volatile uint32_t * const UART_FR = (uint32_t *)0x4000c018;


void
pputchar(const char c)
{
    *UART_DR = c;
}

char
ggetchar()
{
    char c = *UART_DR;
    return c;
}

static char nums[] = "0123456789abcdef";

void
printint(uint32_t value, uint32_t base)
{
    if (value == 0) {
        pputchar('0');
        return;
    }
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
    }
    while (i-- > 0)
        pputchar(buf[i]);
}

void
printptr(uint32_t p_addr)
{
    pputchar('0');
    pputchar('x');
    printint(p_addr, 16);
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
            printint(va_arg(ap, uint32_t), 10);
            break;
        // hex
        case ('x'):
            printint(va_arg(ap, uint32_t), 16);
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
