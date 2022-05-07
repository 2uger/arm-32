#include <stdint.h>

#include "defs.h"
#include "params.h"

struct Thread thread_pool[THREAD_NUM];
struct Thread *current_active_thread;

int global_pid = 1;

struct Thread *
get_current_active_thread()
{
    return current_active_thread;
}

int
get_next_pid()
{
    return global_pid++;
}

void
init_thread_pool()
{
    kprintf("Initialise thread pool\n");
    int thread_num = 0;
    struct Thread *t;
    for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
        t->pid = get_next_pid();
        t->state = UNUSED;
        t->sp = 0x20003000 + thread_num * THREAD_SIZE;
        t->pc = (int)&user_space_code;
    }
}

void
scheduler()
{
    kprintf("Run scheduler\n");
    struct Thread *t;
    while (1) {
        for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
            // kprintf("Got thread to execute with %d pid\n", t->pid);
            t->state = USED;
            current_active_thread = t;
            activate(t);
            // Thread stop executing, get back into kernel mode
            // deactivate();
            // kprintf("Stop executing thread with %d pid\n", t->pid);
        }
    }
}
