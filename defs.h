#include <stdint.h>
#include "scheduler.h"

void activate(struct Thread * thread);

void init_thread_pool();
void scheduler();

void pputchar(const char);
char ggetchar();
void kprintf(char *, ...);

void user_space_code();

void svc();
void system_call();
