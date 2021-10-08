//
// Module for testing
//
#include <stdint.h>

#include "defs.h"
#include "fs.h" 

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
test_block(void)
{
    kprintf("Test of file system\n");
    struct CacheBuffer* sb;
    sb = bread(0, 0);
    kprintf("%s\n", sb->data);
}

void
test_inode(void)
{
    struct inode *in;
    in = ialloc(0, FILE);
    in->size = 4096;
    iupdate(in);
}

void
test(void)
{
    init_disk();
    init_fs(0);
    print_disk();
    test_inode();
    print_disk();
}
