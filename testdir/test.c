#include <stdio.h>

int
main(void) 
{
    char c = 'h';
    int m;
    for (int i = 0; i < 8; i++) {
        m = 1 << (i % 8);
        printf("%d\n", i%8);
    }
    return 0;
}
