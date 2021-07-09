#include "defs.h"
#include "memlayout.h"
#include "proc.h"
#include "param.h"

struct cpu; 

struct proc proc[NPROC];

uint32_t nextpid = 1;

static uint32_t allocpid() {
    int newpid = nextpid;
    nextpid += 1;
    return newpid;
}

// return 0 if cant find place for new process
static struct proc * allocproc(void) {
    struct proc * newproc;
    
    for (newproc = proc; newproc < &proc[NPROC]; newproc++) {
        if (newproc->state == UNUSED) {
            newproc->state = USED;
            newproc->pid = allocpid();

            return newproc;
        }
    }
    return 0;
}

// preparing proc table while booting
void procinit(void) {
    struct proc *proc;
    
    int i = 1;
    for (proc = proc; proc < &proc[NPROC]; proc++) {
        proc->ustack = USPACE_BASE + PROC_SIZE * i;
        i++;
    }
}

// Code that first user process will execute
uint32_t initcode[] = { 
};

void userinit(void) {
    // init first user process, basically beside of allocate
    // place in processes array we copy simple code and just 
    // jump to it
    printf("We are in userinit, trying to run first user process!!!!\n");
    struct proc * newproc;
    newproc = allocproc();

    // copy start code to user process
    memmove(USPACE_BASE, initcode, sizeof(initcode));

    newproc->state = READY;
}

void scheduler(void) {
    struct proc * proc;
    struct cpu * cpu;
    
    /* Iterate through all proccess to check which one is
     * ready to execute => switch context
    */
    printf("We are in scheduler, congrats!!!\n");
    while (1) {
        for (proc = proc; proc < &proc[NPROC]; proc++) {
            if (proc->state == READY) {
                proc->state = RUNNING;
                cpu->proc = proc;
                // make context switch
                activate(proc->ustack) 
            }
        }  
    }
}
