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

void
set_active_thread(struct Thread *t)
{
    cpu.active_thread = t;
}

void
print_thread_info(struct Thread *t)
{
    kprintf("Thread: pid - %d, stack - %x, pc - %x\n", t->pid, t->stack_frame.sp, t->stack_frame.pc);
}

struct Thread *
get_next_unused_thread()
{
    struct Thread *t;
    for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
        if (t->state == RUNNABLE && cpu.active_thread->pid != t->pid) return t;
    }
    kprintf("ERROR: run out of the threads\n");
    return 0;
}

int
get_next_pid()
{
    return global_pid++;
}

void
init_thread_pool()
{
    kprintf("Initialize thread pool\n");
    int thread_num = 0;
    struct Thread *t;
    for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
        t->pid = get_next_pid();
        t->state = UNUSED;
        t->stack_frame.sp = 0x20003000 + thread_num * THREAD_SIZE;
        t->stack_frame.psr = 0x21000000;
        thread_num++;
    }
}

void
init_first_user_thread()
{
    kprintf("Initialize first user thread\n");
    struct Thread *t = &thread_pool[0];
    t->state = RUNNABLE;
    t->stack_frame.pc = (int)&init;
}

void
scheduler()
{
    kprintf("Run scheduler\n");
    struct Thread *t;
    while (1) {
        for (t = thread_pool; t < &thread_pool[THREAD_NUM]; t++) {
            if (t->state == RUNNABLE) {
                kprintf("Got thread to execute with %d pid\n", t->pid);
                t->state = RUNNING;
                set_active_thread(t);
                userret(t);
                // Thread stop executing
                t->state = UNUSED;
                kprintf("Stop executing thread with %d pid\n", t->pid);
            }
        }
        break;

    }
}
