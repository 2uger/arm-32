#include "stdint.h"

#include "defs.h"

char greetings[] = "Hello, from User space!!!\n";

int
task_1()
{
    kprintf("Task 1");
    while(1) {
    };
    return 0;
}

int
task_2()
{
    kprintf("Task 2");
    while(1) {
    };
    return 0;
}
