#include "defs.h"

// registers for sys tick interrupt setup
#define STCTRL      (*( ( volatile unsigned long *) 0xE000E010 ))
#define STRELOAD    (*( ( volatile unsigned long *) 0xE000E014 ))
#define STCURR      (*( ( volatile unsigned long *) 0xE000E018 ))

#define SBIT_ENABLE     0
#define SBIT_TICKINT    1
#define SBIT_CLKSOURCE  2


/* 100000000Mhz * 1ms = 1000000 - 1 */
#define RELOAD_VALUE  9999999

void timerinit(void) {
    STRELOAD = RELOAD_VALUE;
    STCTRL = (1<<SBIT_ENABLE) | (1<<SBIT_TICKINT) | (1<<SBIT_CLKSOURCE);
}
