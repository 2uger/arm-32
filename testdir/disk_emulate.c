// Simple emulator of hard drive

#include <stdio.h>
#include "defs.h"

//#define BLOCKS_NUM 16
//#define BLOCK_SIZE 32 

struct block {
    char data[BLOCK_SIZE];        
};

struct block DISK[BLOCKS_NUM];

void
clean_block(struct block *b)
{
    for (int i = 0; i < BLOCK_SIZE; i++)
        b->data[i] = '0';
}

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
        printf("REading from disk\n");
        for (int i = 0; i < BLOCK_SIZE; i++) {
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
    int blocks_num = size / BLOCK_SIZE;
    if (blockn + blocks_num >= BLOCKS_NUM) {
        printf("Out of blocks!\n");
        return -1;
    }

    int byte_counter = 0;

    char *buf = buffer;

    struct block * b;
    b = DISK + blockn;

    int data_size = size;
    while (data_size) {
        clean_block(b);
        for (int i = 0; i < BLOCK_SIZE; i++) {
            if (!data_size)
                break;
            if (*buf == '\0') {
                b->data[i] = '0';
                continue;
            }
            b->data[i] = *buf;
            buf++;
            byte_counter++;
            data_size--;
        }
        b++;
    }
    return byte_counter; 
}

//int
//main(void)
//{
//    init_disk ();
//    print_disk ();
//    char m[] = "Hello world computer is coooooooooool";
//    printf("%d\n", write_disk (0, m, sizeof(m) - 1)); 
//    //write_disk (1, m, sizeof(m) - 1); 
//    char n[] = "New string";
//    write_disk(1, n, sizeof(n) - 1);
//    print_disk ();
//    char big_n[36];
//    read_disk(1, 1, big_n);
//    printf("%s\n", big_n);
//}
