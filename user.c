#include "stdint.h"

#include "defs.h"

int
init()
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