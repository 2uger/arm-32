#ifndef PROC_H
#define PROC_H 

#include "stdint.h"

enum proc_state { UNUSED, USED, SLEEP, READY, RUNNING, ZOMBIE };

struct cpu {
    struct proc* proc;
};

struct trapframe {
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t pc;
};

/* Structure to store all information about process
 * To be able to get all needed information about process
 */
struct proc {
    enum proc_state state;
    uint32_t pid;
    // address of process stack in kernel
    // shows where it's located(low bound)
    uint32_t ustack;
    uint32_t memsize; // how much memory process occupied
    struct trapframe trapframe;
};
#endif
