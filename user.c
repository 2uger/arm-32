#include "stdint.h"

#include "defs.h"

char greetings[] = "Hello, from User space!!!\n";

int
task_1()
{
    kprintf("Task 1\n");
    while(1) {
        kprintf("Task 1\n");
    };
    return 0;
}

int
task_2()
{
    kprintf("Task 2\n");
    while(1) {
        kprintf("Task 2\n");
    };
    return 0;
}
