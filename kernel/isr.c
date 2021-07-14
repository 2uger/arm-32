// Definition of all interrupt handlers in vector table

void nmi_handler(void) {
}

void hardfault_handler(void) {
}

void systick_handler(void) {
    __asm("mrs r0, psp");
    __asm("stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}");
    __asm("pop {r4, r5, r6, r7, r8, r9, r10, r11, r12, lr}");
    __asm("msr PSR, r12");
}
