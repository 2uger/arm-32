#include <stdint.h>

#include "defs.h"
#include "params.h"

struct Cpu cpu;
struct Thread thread_pool[THREAD_NUM];

int global_pid = 1;

struct Thread *
get_current_active_thread()
{
    return cpu.active_thread;
}

struct Thread *
get_next_unused_thread()
{
    struct Thread *t;
    for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
        if (t->state == INACTIVE) return t;
    }
    kprintf("ERROR: run out of the threads\n");
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
        t->state = INACTIVE;
        t->stack_frame.sp = 0x20003000 + thread_num * THREAD_SIZE;
        thread_num++;
        t->stack_frame.pc = (int)&input_loop;
    }
}

void
scheduler()
{
    kprintf("Run scheduler\n");
    struct Thread *t;
    while (1) {
        for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
            if (t->state == INACTIVE) {
                kprintf("Got thread to execute with %d pid\n", t->pid);
                t->state = ACTIVE;
                cpu.active_thread = t;
                activate(t);
                // Thread stop executing
                t->state = INACTIVE;
                kprintf("Stop executing thread with %d pid\n", t->pid);
            }
        }
    }
}
