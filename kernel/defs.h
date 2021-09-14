// Contain all function declaration
#include <stdint.h>

#include "buf.h"
#include "fs.h"
#include "lock.h"

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
void mmemset(void * dst, char value, uint32_t size);
void mmemmove(void * dst, const void * src, uint32_t size);
char *sstrcpy(char *, const char *, uint32_t);

// panic.c
void panic(char *);

// lock.c
void init_lock(struct lock *lck, char *);
void acquire(struct lock *);
void release(struct lock *);

// buf.c
void binit(void);
struct CacheBuffer *bget(uint32_t, uint32_t);
struct CacheBuffer *bread(uint32_t, uint32_t);
void bwrite(struct CacheBuffer *);
void brelease(struct CacheBuffer *);

// disk_emulate.c
void init_disk(void);
uint32_t read_disk(uint32_t, uint32_t, void *);
uint32_t write_disk(uint32_t, void *, uint32_t);
void print_disk(void);

// fs.c
void readspblock(uint32_t, struct spblock *);

uint32_t balloc(uint32_t);



void test(void);


