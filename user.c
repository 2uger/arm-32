#include "stdint.h"

#include "defs.h"

char greetings[] = "Hello, from User space!!!\n";

void
input_loop()
{
    while (1)
    ;
    print(greetings);
}
