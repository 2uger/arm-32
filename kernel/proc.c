#include "memlayou.h"
#include "proc.h"
#include "param.h"

struct cpu; 

struct proc proc[NPROC];

static struct proc * allocproc(void) {
    struct proc * newproc;
    
    for (newproc = proc; newproc < &proc[NPROC]; newproc++) {
        if (newproc->state == UNUSED) {
            break;
        }
    }
    newproc->state = USED;
    newproc->pid = 1 // allocpid();
    
    
    // Clean up all process context registers
    newproc->context.lr = (uint32_t)forkret;
    newproc->context.sp
    return newproc;
}

void forkret(void) {
    
}

// Code that first user process will execute
uint32_t initcode[] = {
    '0x07', '0x01'
    
}

void userinit(void) {
    // init first user process, basically beside of allocate
    // place in processes array we copy simple code and just 
    // jump to it
    struct proc * newproc;
    newproc = allocproc();

    // copy start code to user process
    // COPY_CODE_TO_USER_SPACE();

    newproc->trapframe->pc = USER_SPACE_BASE;
    newproc->trapframe->sp = PROC_SIZE;

    newproc->memsize = PROC_SIZE;

    newproc->state = READY;
}

void scheduler(void) {
    struct proc * proc;
    struct cpu * cpu;
    
    /* Iterate through all proccess to check which one is
     * ready to execute => switch context
    */
    while () {
        for (proc = proc; proc < &proc[NPROC]; proc++) {
            if (proc->state == READY) {
                // make context switch
                proc->state = RUNNING;
                cpu->proc = proc;
                swtch(&cpu->context, &proc->context)
            }
        }  
    }
}
