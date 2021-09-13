// Definition of all interrupt handlers in vector table
#include "defs.h"

void
nmi_handler(void)
{
    kprintf("We are in nmi handler\n");
    while(1){};
}

void
hardfault_handler(void)
{
    kprintf("We are in hardfault handler\n");
    while(1){};
}

void
memory_manag_fault(void)
{
    while(1){};
}

void
bus_fault(void)
{
    while(1){};
}

void
usage_fault(void)
{
    while(1){};
}

void
svc_call(void)
{
    kprintf("We actually in svc call handler\n");
    while(1){};
}

void
pend_sv(void)
{
}

void
systick_handler(void)
{
    //__asm("mrs r0, psp");
    //__asm("stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}");
    //__asm("pop {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}");
    //__asm("msr PSR, r12");
    kprintf("Sys tick handler");
    for (int i=0; i<1000000; i++) {
    }
    return;
}
