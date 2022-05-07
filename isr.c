#include <stdint.h>

#include "defs.h"


void
svc()
{
    __asm__("push {lr}");
    __asm__("bl kprintf");
    __asm__("pop {pc}");
    __asm__("bx lr");
}
