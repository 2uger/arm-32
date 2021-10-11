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
    ilock(in);
    char m[] = "String for inode";
    kprintf("%s\n", m);
    writei(in, m, 0, sizeof(m));
    char n[20];
    readi(in, n, 0, 20);
    kprintf("Result is %s\n", n);
}

void
test_strcmp(void)
{
    char l[] = "Hellorer";
    char r[] = "Hellowew";
    kprintf("%d\n", sstrcmp(l, r, 2));
    kprintf("%d\n", sstrcmp(l, r, 5));
    kprintf("%d\n", sstrcmp(l, r, 6));
}

void
test(void)
{
    init_disk();
    init_fs(0);
    test_inode();
}
