#include <stdint.h>

#include "defs.h"
#include "params.h"

struct Cpu cpu;
struct Thread thread_pool[THREAD_NUM];

int global_pid = 1;

struct Thread *
get_current_active_thread()
{
    // cpu.active_thread->state = UNUSED;
    return cpu.active_thread;
}

struct Thread *
get_next_unused_thread()
{
    struct Thread *t;
    for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
        if (t->state == UNUSED) return t;
    }
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
        t->stack_frame.sp = 0x20003000 + thread_num * THREAD_SIZE;
        thread_num++;
        t->stack_frame.pc = (int)&user_space_code;
    }
}

void
scheduler()
{
    kprintf("Run scheduler\n");
    struct Thread *t;
    // irq_off();
    while (1) {
        for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
            // kprintf("Got thread to execute with %d pid\n", t->pid);
            t->state = USED;
            cpu.active_thread = t;
            // irq_on();
            activate(t);
            // Thread stop executing, get back into kernel mode
            t->state = UNUSED;
            for (int i = 0; i < 1000000000; i++) {
                continue;
            }
            // kprintf("Stop executing thread with %d pid\n", t->pid);
        }
    }
}
