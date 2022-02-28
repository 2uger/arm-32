#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

#define THREAD_NUM 1

struct Thread {
    int pid;
    int state;
    int sp;
    int pc;
};
#endif
