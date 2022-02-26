#include <stdint.h>

#define THREAD_NUM 2

typedef struct {
    int pid;
    int state;
    int sp;
    int pc;
} Thread;

