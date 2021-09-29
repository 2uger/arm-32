// Definition of all interrupt handlers in vector table
#include "defs.h"
#include "proc.h"

void
nmi_handler(void)
{
    kprintf("NMI handler\n");
    while(1){};
}

void
hardfault_handler(void)
{
    kprintf("Hardfault handler\n");
    while(1){};
}

void
memory_manag_fault_handler(void)
{
    while(1){};
}

void
bus_fault_handler(void)
{
    while(1){};
}

void
usage_fault_handler(void)
{
    while(1){};
}

// user make svc call to make system call
// get call number from r6
void
svc_handler(void)
{
    kprintf("SVC handler\n");

    struct proc* p = myproc();
    save_uregs(&p->trapframe);
    kprintf("Save user regs %x, %x, %x\n", p->trapframe.r2, p->trapframe.r6, p->trapframe.pc);
    while(1) {};
    sys_call(p->trapframe.r6);
}

void
pend_sv(void)
{
}

void
systick_handler(void)
{
    //__asm("mrs r0, CONTROL");
    //__asm("stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}");
    //__asm("pop {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}");
    //__asm("msr PSR, r12");
    kprintf("Sys tick handler");
    for (int i=0; i<1000000; i++) {
    }
    return;
}
