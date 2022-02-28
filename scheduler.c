#include <stdint.h>

#include "defs.h"

struct Thread thread_pool[THREAD_NUM];
int global_pid = 1;

char m = 'h';
int n = 'h';

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
            if (thread->state == 1) {
                activate(thread);
            }
        }
    }
}
