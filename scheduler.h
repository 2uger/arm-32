#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

struct StackFrame {
    int r0;
    int r1;
    int r2;
    int r3;
    int r12;
    int lr;
    int pc;
    int psr;
    int sp;
};

struct Thread {
    int pid;
    int state;
    struct StackFrame stack_frame;
};

struct Cpu {
    struct Thread *active_thread;
};

enum thread_state { UNUSED, USED };

#endif
