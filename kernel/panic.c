#include <stdint.h>

#include "defs.h"

void
panic (char *s)
{
    kprintf("Got KERNEL PANIC with message:\n %s\n", s);
    for(;;)
        ;
}
