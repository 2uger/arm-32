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

void
systick_handler()
{
    kprintf("In systick handler\n");

    struct Thread *t = get_current_active_thread();
    kprintf("Current thread pid: %d\n", t->pid);
    for (int i = 0; i < 1000000000; i++) {
        continue;
    }
    return;
}
