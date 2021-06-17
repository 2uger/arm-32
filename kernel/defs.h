// Contain all function declaration

// proc.c
void scheduler(void);
void userinit(void);

// console.c
void consoleinit(void);
void printf(const char * s);

// uart.c
void uart_init(void);
void uart_sendchar(const char c);

// switch.c
void contextswitch();
