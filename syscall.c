#include <stdint.h>

#include "defs.h"


void
syscall()
{
    struct Thread *t = get_current_active_thread();
    char cmd[10];
    char *cs = t->stack_frame.r0;
    char *dst = &cmd[0];
    sstrcpy(cs, dst, 5);
    if (strncmp(cs, "hello", 4) == 0) {
        kprintf("You call hello\n");
    } else if (strncmp(cs, "world", 4) == 0) {
        kprintf("You call world\n");
    } else {
        kprintf("I don't really understand\n");
    }
    return;
}