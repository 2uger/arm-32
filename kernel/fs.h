#ifndef FS_H
#define FS_H

#include <stdint.h>

#include "param.h"

#define INODES_PER_BLOCK (BLOCK_SIZE / sizeof(struct dinode))

// block containing inode
#define IBLOCK(i, sb) ((i/INODES_PER_BLOCK) + sb.inodes_start)

// bitmap bits per block
#define BPB (BLOCK_SIZE * 8) // as we measure block size in bytes

// block containing bitmap bit for demanding block
#define BMBLOCK(b, spb) ((b/BPB) + spb.bitmap_start)


// superblock
struct spblock {
    uint32_t magic; // FS magic number, used to recognize file system
    uint32_t size;  // FS blocks amount

    uint32_t data_blocks_num;
    uint32_t inodes_num;

    uint32_t inodes_start; // block where inodes start
    uint32_t bitmap_start; // block where bitmap start
};

// disk inode structure
struct dinode {
    uint8_t type; // identify type of information(file, dir, device). 0 means free.
    uint16_t nlink; // how much dirs link to that file
    uint32_t size; // how much data in file
    uint32_t addrs[DATA_BLOCKS_NUM]; // addresses of all file's blocks
};

// memory inode structre
struct inode {
    uint32_t dev; // device number
    uint32_t inum; // i node number
    uint32_t ref_count; // count all reference from C code(pointers), remove when 0
    uint8_t valid; // usage: when find free place in inode table, but dont read from disk

    // same structure as in disk i node
    uint16_t type; // identify type of information(file, dir, device). 0 means free.
    uint16_t nlink; // how much dirs link to that file
    uint32_t size; // how much data in file
    uint32_t addrs[DATA_BLOCKS_NUM]; // addresses of all file's blocks
};

#endif
