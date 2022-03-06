#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>

#define THREAD_NUM 3

struct Thread {
    int pid;
    int state;
    int sp;
    int pc;
};
#endif
