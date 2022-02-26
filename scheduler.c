#include <stdint.h>

#include "defs.h"


Thread thread_pool[THREAD_NUM];
static int global_pid = 0;

int
get_next_pid()
{
    return global_pid++;
}

void
init_thread_pool()
{
    Thread * thread;
    thread = thread_pool;
    for (thread = thread_pool; thread < &thread_pool[THREAD_NUM]; thread++) {
        thread->pid = get_next_pid();
        thread->state = 0;
        thread->sp = 0;
        thread->pc = 0;
    }
}

void
scheduler()
{
    Thread * thread;
    while (1) {
        for (thread = thread_pool; thread < &thread_pool[THREAD_NUM]; thread++) {
            if (thread->state == 0) {
                fprint("Switch into user space");
                activate(thread);
                fprint("Get back from user space");
            }
        }
    }
}
