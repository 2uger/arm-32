#include "stdint.h"

#include "defs.h"

void
setup()
{
    uartinit();
    // timerinit();
    init_thread_pool();
    init_first_user_thread();
    scheduler();
}