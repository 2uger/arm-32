#include "stdint.h"

enum proc_state { UNUSED, USED, SLEEP, READY, RUNNING, ZOMBIE };

struct cpu {
    struct proc * proc;
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
};
