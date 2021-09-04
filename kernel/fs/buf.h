#ifndef BUF_H
#define BUF_H

#define BCACHE_NUM 4 
#define BLOCK_SIZE 4 

typedef int uint32_t;
typedef int uint16_t;

struct CacheBuffer {
    uint32_t valid;
    uint16_t dirty; // data should we written into disk

    uint32_t dev; // device number
    uint32_t blockn; // block number on disk
    
    uint16_t refcnt; // users amount

    uint32_t data[BLOCK_SIZE]; // actual data
    
    struct CacheBuffer *next;
    struct CacheBuffer *prev;
};

#endif