#include <stdint.h>

#include "defs.h"

void
setup()
{
    scheduler();
}

void
svc()
{
    __asm__("bl pputchar");
    __asm__("mov r0, #0x42");
    __asm__("bl pputchar");
    __asm__("ldr r1, =0x0");
    __asm__("msr CONTROL, r1");
    __asm__("pop {lr}");
}

void
system_call()
{
}
