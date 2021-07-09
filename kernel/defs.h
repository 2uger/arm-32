// Contain all function declaration

// proc.c
void scheduler(void);
void userinit(void);
void procinit(void);

// console.c
void consoleinit(void);
void printf(const char *, ...);

// uart.c
void uart_init(void);
void uart_sendchar(const char c);

// activate.S
void activate(uint32_t ustack);

// main.c
void main();

//string.c
void memmove(void * dst, const void * src, uint32_t size);
