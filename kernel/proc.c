#include "proc.h"

struct cpu cpus[NCPU];

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
    // newproc->context.lr
    // newproc->context.sp
    return newproc;
}

void userinit(void) {
    struct proc * newproc;
    newproc = allocproc();
    // copy start code to user process
    newproc->state = RUNNABLE;
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
