#include <stdint.h>

#include "defs.h"


void
svc()
{
    __asm__("push {lr}");
    __asm__("bl kprintf");
    __asm__("pop {r1}");
    __asm__("mov lr, r1");
}
