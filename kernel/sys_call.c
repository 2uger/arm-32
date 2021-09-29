#include "defs.h"

//extern uint32_t sys_fork(void);
//extern uint32_t sys_exec(void);
//extern uint32_t sys_kill(void);
//extern uint32_t sys_open(void);
//extern uint32_t sys_close(void);
//extern uint32_t sys_read(void);
//extern uint32_t sys_write(void);
void sys_fork(void) {}

static uint32_t (*syscalls[])(void) = {
    [1] sys_fork

};

void
sys_call(uint32_t num)
{
    syscalls[0];
    return;
}
