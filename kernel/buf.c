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

#include "param.h"

struct CacheBuffer {
    uint32_t valid;
    uint16_t dirty; // data should we written into disk

    uint32_t dev; // device number
    uint32_t blockn; // block number on disk
    
    uint16_t refcnt; // to not use buffer for different disk block

    uint32_t data[BLOCK_SIZE]; // actual data
    
    struct CachBuffer *next;
    struct CachBuffer *prev;
}

struct {
    struct CacheBuffer buf[BCACHE_NUM];

    // Most recent used
    struct CacheBuffer *head;
    // Least recent used
    struct CacheBuffer *tail;
} bcache;

// Init cache buffer
// Actually initialize list like a cyclic loop
void
binit(void)
{
    struct CacheBuffer *b;
    bcache.head = bcache.buf;
    bcache.tail = bcache.buf;

    for (b = &bcache.buf[1]; b < bcache.buf+BCACHE_NUM; b++) {
        b->prev = bcache.tail;
        b->prev->next = b;
        bcache.tail = b;
    }
    b->next = head;
    b->next->prev = b;
}

// Scan through array and find 
struct CacheBuffer * 
bget(uint32_t dev, uint32_t blockn)
{
    //Scan buffer array, if find return, else allocate a new one
    CacheBuffer *buf;
    buf = bcache.head;
    
    while (buf <= bcache.tail) {
        // find block with same dev and block num
        if (buf->dev == dev && buf->blockn == blockn) {
            buf->refcnt++;
            return buf;
        }
        buf++;
    }
    
    // dont find demanding block, allocate a new one
    buf = bcache.head;
    while (buf <= bcache.tail) {
        if (buf->refcnt == 0) {
            buf->dev = dev;
            buf->blockn = blockn;
            buf->valid = 0;
            buf->refcnt = 1;
            return buf;
        }
    }
    panic("Cant allocate new free cache buffer\n");
    
}

// Return buffer with actual data
struct CacheBuffer * 
bread(uint32_t dev, uint32_t blockn)
{
    // Call bget, if it's new, call read routine from sd card
    struct CacheBuffer *buf;
    
    buf = bget(dev, blockno);
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
    // Write buffer content into sd card
    write_disk(buf->blockn, buf->data, sizeof(buf->data)-1);
}

void
brelease(struct CacheBuffer *buf)
{
    buf->refcnt--;
    // check if buffer is not needed anymore
    // buffer is most recently used, move it to the head of list
    if (buf->refcnt == 0 && head != buf) {
        if (tail == buf)
            tail = tail->prev;
        // remove buffer
        buf->prev->next = buf->next;
        buf->next->prev = buf->prev; 
        
        // change head pointer
        head->prev->next = buf;
        head->prev = buf;
        buf->next = head;
        head = buf;
    } 
}
