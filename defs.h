#include <stdint.h>
#include "scheduler.h"

void activate(struct Thread *thread);

struct Thread * get_current_active_thread(void);
void init_thread_pool();
void scheduler();

void pputchar(const char);
char ggetchar();
void kprintf(char *, ...);

void user_space_code(const char *s);
void print(const char *s);

void svc();
void system_call();

void timerinit(void);
