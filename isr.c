#include <stdint.h>

#include "defs.h"

void
svc_handler()
{
    kprintf("SVC handler\n");
    int * kernel_stack = get_kernel_stack_pointer();
    kernelret(kernel_stack);
    struct Thread *active_thread = get_current_active_thread();
    kprintf("PID of active thread is %d\n", active_thread->pid);
}

void
systick_handler()
{
    kprintf("Systick handler\n");

    struct Thread *next_active_thread = get_next_unused_thread();
    if (next_active_thread != 0) {
        kprintf("Next thread to execute pid: %x\n", next_active_thread->pid);
        set_active_thread(next_active_thread);
        swtch(next_active_thread);
        //userret(next_active_thread);
    }
    //uct Thread *active_thread = get_current_active_thread();
    //struct Thread *unused_thread = get_next_unused_thread();

    // kprintf("Current thread pid: %x\n", active_thread->stack_frame.sp);
    // kprintf("Unused thread pid: %x\n", unused_thread->stack_frame.sp);

    // for (int i = 0; i < 1000000000; i++) {
    //     continue;
    // }

}

void
pendsv_handler()
{
    kprintf("PendSV handler\n");
}

void
default_handler()
{
    int m = 1;
    int n = m + 2;
    kprintf("Default handler\n");

    while (1)
    ;
}
