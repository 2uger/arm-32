#define "defs.h"

void main() {
    consoleinit();
    printf("\n");
    printf("Kernel is booting up, just wait and relax!!!");
    printf("\n");
    trapinit();
    userinit();
    scheduler();
}
