#include <stdio.h>
#include "defs.h"
#include "buf.h"

int
main(void)
{
    init_disk();
    print_disk();
    char str[] = "Hello world god,damn bro,";
    int bytes = write_disk(0, str, sizeof(str)); 
    printf("%d\n", bytes);
    print_disk();
    char read_string[sizeof(str)];
    read_disk(3, 2, read_string);
    printf("%s\n", read_string);
    binit();
    print_buffer_addrs();
}
