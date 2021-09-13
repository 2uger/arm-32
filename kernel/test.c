//
// Module for testing
//
#include <stdint.h>

#include "defs.h"

void
test_printf(void)
{
    kprintf("*********  Start test of printf function  *********\n");
    kprintf("Output for decimal %d, %d, %d\n", 1324231, 0, 132);
    kprintf("Output for hex %x, %x, %x\n", 16, 256, 132);
    int m = 2;
    int k = 5;
    kprintf("Output for address %p, %p\n", &m, &k);
    kprintf("Output for character %c, %c, %c\n", 'm', 'R', 'l');
    kprintf("Output for string %s\n", "Hello world!");
}

void
test(void)
{
    test_printf();
    init_disk();
    print_disk();
}
