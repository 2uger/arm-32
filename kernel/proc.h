// Storing process context
// Basically it's just like register environment
// Context used by kernel itself to run next process
struct context {
    uint32_t r0;
    uint32_t r1;
    uint32_t r2;
    uint32_t r3;
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t r12;

    // Only need to know where is process stack
    // And address where process should start from
    uint32_t sp;
    uint32_t lr;
}

// While trapframe used when interrupt happened
struct trapframe {
    uint32_t sp;
    uint32_t pc;
}

enum proc_state { UNUSED, USED, SLEEP, READY, RUN, ZOMBIE };

struct cpu {
    struct proc * proc;
    struct context context; 
}

/* Structure to store all information about process
 * To be able to get all needed information about process
 */
struct proc {
    enum proc_state state;
    uint32_t pid;

    uint32_t memsize; // how much memory process occupied
    struct trapframe * trapframe;
    struct context * context;
}
