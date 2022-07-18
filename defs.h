#include <stdint.h>
#include "scheduler.h"

void swtch(struct Thread *);
void userret(struct Thread *);
void firstret(struct Thread *);
void kernelret(struct Thread *);

int * get_kernel_stack_pointer(void);
struct Thread * get_current_active_thread(void);
void set_active_thread(struct Thread *);
struct Thread * get_next_unused_thread(void);
void init_thread_pool();
void scheduler();

void pputchar(const char);
char ggetchar();
void kprintf(char *, ...);

void user_space_code(const char *s);
int task_1();
int task_2();
void print(const char *s);

void timerinit(void);

void irq_on(void);
void irq_off(void);