// Fake UART just for testing
// Will setup it in normal mode when
// Test on real hardware
#include "stdint.h"

int i = 12;
char m[] = "Hello world";

void
print_char(char c)
{
    __asm("ldr r1, =0x4000c000");
    __asm("str r0, [r1]");
    __asm("bx lr");
}

void
fprint(char * s)
{
    char * c = s;
    while (*c != '\n')
        print_char(*c++);
}
