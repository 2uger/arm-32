#include "defs.h"

// Serve first user process and others initialization
// here we jump to the user mode
void
main()
{
    consoleinit ();  
    kprintf("Kernel is booting up, just wait and relax!!!\n");

    procinit ();

    userinit ();
    scheduler ();
}
