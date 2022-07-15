#include "stdint.h"

#include "defs.h"

char greetings[] = "Hello, from User space!!!\n";

void
input_loop()
{
    call_svc(greetings);
}
