#include <stdint.h>
#include "scheduler.h"

void setup();

void activate(struct Thread * thread);

void init_thread_pool();
void scheduler();

void user_space_code();
