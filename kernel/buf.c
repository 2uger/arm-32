// Disk simple double linked list of buffer caches
// Buffer cache actually hold information of one disk block
// Cache work by simple principle: LRU

// binit -- init buffer cache
// bread -- read a disk block
// bwrite -- write a disk block
// brelease -- release disk block

// TODO:
// *** Need interface to sd card, emulate it with array and some calls
// *** Start with simple buffer cache, double linked list
// *** Think about how double linked list should be init so we can
// follow on last recently buffer
#include <stdint.h>

#include "defs.h"
#include "param.h"
#include "buf.h"

struct {
    struct CacheBuffer buf[BCACHE_NUM];
} bcache;

// Init cache buffer
// Actually initialize list like a cyclic loop
void
binit(void)
{
    struct CacheBuffer *b;

    for (b = bcache.buf; b < &bcache.buf[BCACHE_NUM]; b++) {
        b->valid = 0;
        b->dirty = 0;

        b->dev = 0;
        b->blockn = 0;
        b->refcnt = 0;
    }
}

// Scan through array and find 
struct CacheBuffer* 
bget(uint32_t dev, uint32_t blockn)
{
    //Scan buffer array, if find return, else allocate a new one
    struct CacheBuffer *buf;


    for (buf = bcache.buf; buf < &bcache.buf[BCACHE_NUM]; buf++) {
        // find block with same dev and block num
        if (buf->blockn == blockn) {
            buf->refcnt++;
            return buf;
        }
    }
    
    // dont find demanding block, allocate a new one
    for (buf = bcache.buf; buf < &bcache.buf[BCACHE_NUM]; buf++) {
        if (buf->refcnt == 0) {
            buf->dev = dev;
            buf->blockn = blockn;
            buf->valid = 0;
            buf->refcnt = 1;
            return buf;
        }
    }
    panic("can't allocate new free cache buffer");
}

// Return buffer with actual data
struct CacheBuffer* 
bread(uint32_t dev, uint32_t blockn)
{
    struct CacheBuffer* buf;
    
    // call bget, if it's new, call read routine from sd card
    buf = bget(dev, blockn);
    if (!buf->valid) {
        // read into buffer from disk
        read_disk(blockn, 1, buf->data); 
        buf->valid = 1;
    }
    return buf;
}

void
bwrite(struct CacheBuffer *buf)
{
    struct CacheBuffer *b;


    for (b = bcache.buf; b < &bcache.buf[BCACHE_NUM]; b++) {
        kprintf("%d, %d, %s\n", b->dev, b->blockn, b->data);
    }
    // Write buffer content into sd card
    write_disk(buf->blockn, buf->data, sizeof(buf->data));
}

void
brelease(struct CacheBuffer *buf)
{
    buf->refcnt--;
}
