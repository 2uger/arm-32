// Simple emulator of hard drive

#include <stdio.h>

#define BLOCKS_NUM 16
#define BLOCK_SIZE 32 

struct block {
    char data[BLOCK_SIZE];        
};

struct block DISK[BLOCKS_NUM];

void
print_disk(void)
{
    struct block *b;
    for (b = DISK; b < &DISK[BLOCKS_NUM]; b++) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
            printf("%c", b->data[i]);
        }
        printf("\n");
    }
    printf("\n");
}

void 
init_disk()
{
    struct block *b;
    for (b = DISK; b < &DISK[BLOCKS_NUM]; b++) {
        // zeroing all blocks in disk
        int i;
        for (i = 0; i < BLOCK_SIZE; i++) {
            b->data[i] = '0';
        } 
    } 
}

int 
read_disk(int blockn, int blocks_num, void *buffer)
{
    // how many bytes we actually read from disk
    int byte_counter = 0;

    struct block *b;
    b = DISK + blockn;

    char *buf = buffer;
    while (blocks_num) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
            if (!size) {
                *buf = '\0';
                break;
            }
            *buf = b->data[i]; 
            buf++;
            byte_counter++;
        }
        blocks_num--;
        b++;
    }
    return byte_counter;
} 

int
write_disk(int blockn, void *buffer, int size)
{
    if (blockn + size / BLOCK_SIZE >= BLOCKS_NUM) {
        printf("Out of blocks!\n");
        return -1;
    }

    int byte_counter = 0;

    struct block * b;
    b = DISK + blockn;

    char *buf = buffer;
    while (size) {
        for (int i = 0; i < BLOCK_SIZE; i++) {
            if (!size)
                break;
            b->data[i] = *buf;
            buf++;
            byte_counter++;
            size--;
        }
        b++;
    }
    return byte_counter; 
}

int
main()
{
    init_disk ();
    print_disk (); 
    char buf[] = "Hello world hoefkdjkfjdkjfkdjkfdsfj!!!";
    int i = write_disk(4, buf, sizeof(buf)-1);
    printf("Bytes written into disk %d\n", i);
    print_disk (); 
    
    char empty_buffer[100];
    read_disk(4, empty_buffer, 5);
    printf("Buffer after reading from disk:\n%s\n", empty_buffer);
}

