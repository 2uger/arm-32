#include "stdint.h"

#include "defs.h"


int
task_1()
{
    kprintf("Task 1\n");
    int i = 0;
    char cmd[10];
    while(1) {
        char *cs = &cmd[0];
        kprintf(">> ");
        char *ss = ffgets(cs, 5);
        call_svc(ss);
    }
    return 0;
}

int
task_2()
{
    kprintf("Task 2\n");
    while(1) {
    };
    return 0;
}
