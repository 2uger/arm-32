#include "defs.h"

// Serve first user process and others initialization
// here we jump to the user mode
void main() {
    consoleinit();  
    kprintf('\n');
    kprintf("Kernel is booting up, just wait and relax!!!");
    kprintf('\n');

    procinit();

    userinit();
    scheduler();
}
