#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

struct StackFrame {
    int r0;
    int r1;
    int r2;
    int r3;
    int r4;
    int r5;
    int r6;
    int r7;
    int r8;
    int r9;
    int r10;
    int r11;
    int r12;
    int sp;
    int lr;
    int pc;
    int psr;
};

struct Thread {
    int pid;
    int state;
    struct StackFrame stack_frame;
};

struct Cpu {
    struct Thread *active_thread;
};

enum thread_state { UNUSED, USED, READY };

#endif
