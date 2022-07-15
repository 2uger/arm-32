#include <stdint.h>
#include "scheduler.h"

void activate(struct Thread *);

struct Thread * get_current_active_thread(void);
struct Thread * get_next_unused_thread(void);
void init_thread_pool();
void scheduler();

void pputchar(const char);
char ggetchar();
void kprintf(char *, ...);

void user_space_code(const char *s);
void input_loop();
void print(const char *s);

void timerinit(void);

void irq_on(void);
void irq_off(void);