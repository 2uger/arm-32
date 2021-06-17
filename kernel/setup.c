#include <core_cm3.h>

void kernel_setup(void) {
    vtableinit();
    timerinit();
    main();
}

void timerinit(void) {
    SysTick->LOAD = 1023;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x7;
}

void vtableinit(void) {
    // As kernel contain vector table at first
    // of itself image, we just need to setup 
    // right offset
    SCB->VTOR = KERNEL_SPACE_BASE;
}
