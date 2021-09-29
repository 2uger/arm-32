#include <stdint.h>
#include <stdbool.h>

#include "defs.h"
#include "memlayout.h"
#include "proc.h"
#include "param.h"


struct cpu cpu; 

struct proc proc[NPROC];

uint32_t nextpid = 1;

struct proc*
myproc(void)
{
    return cpu.proc;
}

static uint32_t allocpid() {
    return nextpid++;
}

// return 0 if cant find place for new process
static struct proc*
allocproc(void)
{
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
void
procinit(void)
{
    struct proc* p;
    
    int i = 1;
    for (p = proc; p < &proc[NPROC]; p++) {
        p->ustack = USPACE_BASE + PROC_SIZE * i;
        kprintf("Process stack %d is locating at %p\n", i, p->ustack);
        p->state = UNUSED;
        p->memsize = USPACE_BASE + PROC_SIZE * i;
        i++;
    }
}

// Code that first user process will execute
char initcode[] = { 
    0x01, 0x26, 0x09, 0xDF
};

void
userinit(void)
{
    // init first user process, basically beside of allocate
    // place in processes array we copy simple code and just 
    // jump to it
    kprintf("Load first user process\n");
    
    struct proc* newproc;
    newproc = allocproc();

    // copy start code to user process
    mmemmove((uint32_t*)USPACE_BASE, initcode, sizeof(initcode));
    proc->trapframe.pc = USPACE_BASE;

    newproc->state = READY;
    kprintf("Pid of first user process is %d\n", newproc->pid);
}

void
scheduler(void)
{
    struct proc* p;
 
    /* Iterate through all proccess to check which one is
     * ready to execute => switch context
    */
    kprintf("Scheduler start it's work\n");
    while (true) {
        for (p = proc; p < &proc[NPROC]; p++) {
            if (p->state == READY) {
                kprintf("Proc with READY state\n");
                p->state = RUNNING;
                cpu.proc = p;
                // make context switch
                activate(p->ustack, &p->trapframe);
            }
        }  
    }
}

// System call to execute user programm
// Need to read path to programm, load it into
// memory and just start executing
void
exec(char* path, char** argv)
{
}

// System call for make a copy of current process
// and make him as child
void
fork(void)
{
}
