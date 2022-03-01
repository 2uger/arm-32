#include <stdint.h>

#include "defs.h"


void
svc()
{
    __asm__("mrs r1, psp");
    __asm__("ldr r0, [r1, #0]");
    __asm__("ldr r1, [r1, #24]");
    __asm__("ldrb r1, [r1, #-2]");
    __asm__("ldr r1, =0x0");
    __asm__("msr CONTROL, r1");
    __asm__("pop {pc}");
    system_call(2);
}

void
system_call(int call_num)
{
    kprintf("Get %d svc call\n", call_num);
}
