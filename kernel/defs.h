// Contain all function declaration

// proc.c
void scheduler(void);
void userinit(void);
void forkret(void);
void procinit(void);

// console.c
void consoleinit(void);
void printf(const char * s);

// uart.c
void uart_init(void);
void uart_sendchar(const char c);

// switch.c
void contextswitch();

// main.c
void main();
