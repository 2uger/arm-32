#ifndef BUF_H
#define BUF_H

#define BCACHE_NUM 16

struct CacheBuffer {
    uint32_t valid;
    uint16_t dirty; // data should we written into disk

    uint32_t dev; // device number
    uint32_t blockn; // block number on disk
    
    uint16_t refcnt; // to not use buffer for different disk block

    uint32_t data[BLOCK_SIZE]; // actual data
    
    struct CacheBuffer *next;
    struct CacheBuffer *prev;
}

#endif
