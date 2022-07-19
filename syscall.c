#include <stdint.h>

#include "defs.h"

void
syscall()
{
    struct Thread *t = get_current_active_thread();
    switch(t->stack_frame.r2) {
        case 2:
            kprintf("You want to call service 2\n");
            kprintf("You current thread pid: %d\n", t->pid);
            break;
        case 3:
            kprintf("You want to call service 3\n");
            break;
        default:
            kprintf("Unknown service to call\n");
            break;
    }
    return;
}