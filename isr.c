#include <stdint.h>

#include "defs.h"


void
svc()
{
    __asm__("bl kprintf");
    __asm__("pop {lr}");
}
