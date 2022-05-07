#include "stdint.h"

#include "defs.h"

char greetings1[] = "Hello, 1, from User space!!!\n";
char greetings2[] = "Hello, 2, from User space!!!\n";
char greetings3[] = "Hello, 3, from User space!!!\n";

void
input_loop()
{
    switch('1') {
        case '1':
            // print(greetings1);
            break;
        case '2':
            print(greetings2);
            break;
        default:
            print(greetings3);
            break;

    }
}
