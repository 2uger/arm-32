#include <stdint.h>

#include "defs.h"

struct Thread thread_pool[THREAD_NUM];
int global_pid = 1;

int
get_next_pid()
{
    return global_pid++;
}

void
init_thread_pool()
{
    kprintf("Init thread\n");
    struct Thread * t;
    for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
        t->pid = get_next_pid();
        t->state = 0;
        t->sp = 0x20004000;
        t->pc = (int)&user_space_code;
    }
}

void
scheduler()
{
    kprintf("Run scheduler\n");
    struct Thread * t;
    while (1) {
        for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
            kprintf("Got thread to execute with %d pid\n", t->pid);
            t->state = 1;
            activate(t);
            // thread stop executing
            kprintf("Stop executing thread with %d pid\n", t->pid);
        }
        break;
    }
}
