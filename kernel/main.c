#include "core_cm3.h"
#include "defs.h"

// Serve first user process and others initialization
// here we jump to the user mode
void main() {
    consoleinit();
    printf("\n");
    printf("Kernel is booting up, just wait and relax!!!");
    printf("\n");

    procinit();

    userinit();
    scheduler();
}
