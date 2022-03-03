#include <stdint.h>

#include "defs.h"

struct Thread thread;
int global_pid = 1;

int
get_next_pid()
{
    return global_pid++;
}

void
init_thread()
{
    kprintf("Init thread\n");
    struct Thread * t = &thread;
    t->pid = get_next_pid();
    t->state = 0;
    t->sp = 0x20004000;
    t->pc = (int)&user_space_code;
}

void
scheduler()
{
    kprintf("Run scheduler\n");
    struct Thread * t = &thread;
    while (1) {
        kprintf("Got thread to execute with %d pid\n", t->pid);
        t->state = 1;
        activate(t);
        // thread stop executing
        kprintf("Stop executing thread with %d pid\n", t->pid);
        break;
    }
}
