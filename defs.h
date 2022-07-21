#include <stdint.h>
#include "scheduler.h"

void setup();

void swtch(struct Thread *);
void save_ctx(struct Thread *);
void userret(struct Thread *);

struct Thread * get_current_active_thread(void);
void set_active_thread(struct Thread *);
struct Thread * get_next_unused_thread(void);
void print_thread_info(struct Thread *);

void init_thread_pool();
void init_first_user_thread();
void scheduler();

void uartinit();
void pputchar(const char);
char ggetchar();
char * fgets(char *, int);
void kprintf(char *, ...);

void call_svc(char *);
int init();

void timerinit(void);

void irq_on(void);
void irq_off(void);

void syscall();

void mmemset(void * dst, char value, uint32_t size);
void mmemmove(void * dst, const void * src, uint32_t size);
char *sstrcpy(const char *, char *, uint32_t);
int strncmp(const char *p, const char *q, uint32_t n);