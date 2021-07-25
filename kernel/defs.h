// Contain all function declaration
#include <stdint.h>

// proc.c
void scheduler(void);
void userinit(void);
void procinit(void);

// console.c
void consoleinit(void);
void kprintf(char *, ...);
void pputchar(const char);

// uart.c
void uart_init(void);
void uart_sendchar(char);

// activate.S
void activate(uint32_t ustack);

// main.c
void main();

//string.c
void mmemmove(void * dst, const void * src, uint32_t size);

// panic.c
void panic(char *);

// lock.c
void init_lock(struct lock *lck, char *);
void acquire(struct lock *);
void release(struct lock *);
