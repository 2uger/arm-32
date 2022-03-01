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
    kprintf("Init thread pool\n");
    struct Thread * thread;
    for (thread = thread_pool; thread < &thread_pool[THREAD_NUM]; thread++) {
        thread->pid = get_next_pid();
        thread->state = 0;
        thread->sp = 0x20002000;
        thread->pc = (int)&user_space_code;
    }
}

void
scheduler()
{
    kprintf("Run scheduler\n");
    struct Thread * thread;
    while (1) {
        for (thread = thread_pool; thread < &thread_pool[THREAD_NUM]; thread++) {
            if (thread->state == 0) {
                kprintf("Got thread to execute with %d pid\n", thread->pid);
                thread->state = 1;
                activate(thread);
                // thread stop executing
                thread->state = 0;
                kprintf("Stop executing thread with %d pid\n", thread->pid);
            }
            break;
        }
        break;
    }
}
