// Simple emulator of hard drive

#include <stdint.h>

#include "defs.h"
#include "param.h"


struct block {
    char data[BLOCK_SIZE];        
};

struct block DISK[BLOCKS_NUM];

void
clean_block(struct block *b)
{
    for (uint32_t i = 0; i < BLOCK_SIZE; i++)
        b->data[i] = '0';
}

void
print_disk(void)
{
    struct block *b;
    for (b = DISK; b < &DISK[BLOCKS_NUM]; b++) {
        for (uint32_t i = 0; i < BLOCK_SIZE; i++) {
            kprintf("%c", b->data[i]);
        }
        kprintf("\n");
    }
    kprintf("\n");
}

void 
init_disk(void)
{
    struct block *b;
    for (b = DISK; b < &DISK[BLOCKS_NUM]; b++) {
        // zeroing all blocks in disk
        uint32_t i;
        for (i = 0; i < BLOCK_SIZE; i++) {
            b->data[i] = 0;
        } 
    } 
}

uint32_t 
read_disk(uint32_t blockn, uint32_t blocks_num, void *buffer)
{
    // how many bytes we actually read from disk
    uint32_t byte_counter = 0;

    struct block *b;
    b = DISK + blockn;

    char *buf = buffer;
    while (blocks_num) {
        for (uint32_t i = 0; i < BLOCK_SIZE; i++) {
            *buf = b->data[i]; 
            buf++;
            byte_counter++;
        }
        blocks_num--;
        b++;
        // avoid reading from DISK bound
        if (b > &DISK[BLOCKS_NUM])
            break;
    }
    return byte_counter;
} 

uint32_t
write_disk(uint32_t blockn, void *buffer, uint32_t size)
{
    uint32_t blocks_num = size / BLOCK_SIZE;
    if (blockn + blocks_num >= BLOCKS_NUM) {
        kprintf("Out of blocks!\n");
        kprintf("%d, %d\n", blockn, blocks_num);
        return -1;
    }

    uint32_t byte_counter = 0;

    char *buf = buffer;

    struct block * b;
    b = DISK + blockn;

    uint32_t data_size = size;
    uint32_t stop_write = 0;
    while (data_size) {
        clean_block(b);
        for (uint32_t i=0; i<BLOCK_SIZE; i++) {
            b->data[i] = *buf;
            buf++;
            byte_counter++;
            data_size--;
            if (data_size == 1) {
                stop_write = 1;
                break;
            }
        }
        if (stop_write)
            break;
        b++;
    }
    return byte_counter; 
}
