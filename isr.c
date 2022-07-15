#include <stdint.h>

#include "defs.h"

void
svc_handler()
{
    kprintf("SVC handler\n");
    irq_on();
    char buf[10];
    while (1) {
        char c = ggetchar();
        pputchar(c);
    };
    kprintf(buf);
    kprintf("\n");
    while (1) {};
    struct Thread *active_thread = get_current_active_thread();
    kprintf("PID of active thread is %d\n", active_thread->pid);
}

void
systick_handler()
{
    kprintf("Systick handler\n");

    //struct Thread *active_thread = get_current_active_thread();
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
    kprintf("Default handler\n");

    while (1)
    ;
}
