#include "param.h"

// disk inode structure
struct dinode {
    uint16_t type; // identify type of information(file, dir, device). 0 means free.
    uint16_t nlink; // how much dirs link to that file
    uint32_t size; // how much data in file
    uint32_t addrs[FILE_BLOCKS_NUM]; // addresses of all file's blocks
}

// memory inode structre
struct inode {
    uint32_t dev; // device number
    uint32_t inum; // i node number
    uint32_t ref_count; // count all reference from C code, remove when 0

    // same structure as in disk i node
    uint16_t type; // identify type of information(file, dir, device). 0 means free.
    uint16_t nlink; // how much dirs link to that file
    uint32_t size; // how much data in file
    uint32_t addrs[FILE_BLOCKS_NUM]; // addresses of all file's blocks
    
}
