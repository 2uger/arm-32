#include "core_cm3.h"
#include "defs.h"

void main() {
    consoleinit();
    printf("\n");
    printf("Kernel is booting up, just wait and relax!!!");
    printf("\n");

    userinit();
    scheduler();
}
