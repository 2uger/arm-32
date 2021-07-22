// Definition of all interrupt handlers in vector table
#include "defs.h"

void nmi_handler(void) {
    kprintf("We are in nmi handler\n");
}

void hardfault_handler(void) {
    kprintf("We are in hardfault handler\n");
}

void memory_manag_fault(void) {
}

void bus_fault(void) {
}

void usage_fault(void) {
}

void svc_call(void) {
    kprintf("We actually in svc call handler\n");
}

void pend_sv(void) {
}

void systick_handler(void) {
    __asm("mrs r0, psp");
    __asm("stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}");
    __asm("pop {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}");
    __asm("msr PSR, r12");
}
