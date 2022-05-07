#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

struct StackFrame {
    int r0;
    int r1;
    int r2;
    int r12;
    int lr;
    int pc;
    int psr;
};

struct Thread {
    int pid;
    int state;
    int sp;
    int pc;
    struct StackFrame stack_frame;
};

enum thread_state { UNUSED, USED };

#endif
