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

#include "stdio.h"
#include "string.h"
#include "defs.h"

#define BCACHE_NUM 16



struct CacheBuffer {
    int valid;
    int dirty; // data should we written into disk

    int dev; // device number
    int blockn; // block number on disk
    
    int refcnt; // to not use buffer for different disk block

    char data[BLOCK_SIZE]; // actual data
    
    struct CacheBuffer *next;
    struct CacheBuffer *prev;
};

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

    for (b = bcache.buf+1; b < bcache.buf+BCACHE_NUM; b++) {
        b->prev = bcache.tail;
        b->prev->next = b;
        bcache.tail = b;
    }
    bcache.tail->next = bcache.head;
    bcache.head->prev = bcache.tail;
}

// Scan through array and find 
struct CacheBuffer * 
bget(int dev, int blockn)
{
    //Scan buffer array, if find return, else allocate a new one
    struct CacheBuffer *buf;
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
}

// Return buffer with actual data
struct CacheBuffer * 
bread(int dev, int blockn)
{
    // Call bget, if it's new, call read routine from sd card
    struct CacheBuffer *buf;
    
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
    // Write buffer content into sd card
    write_disk(buf->blockn, buf->data, sizeof(buf->data));
}

void
brelease(struct CacheBuffer *buf)
{
    buf->refcnt--;
    // check if buffer is not needed anymore
    // buffer is most recently used, move it to the head of list
    if (buf->refcnt == 0 && bcache.head != buf) {
        if (bcache.tail == buf)
            bcache.tail = bcache.tail->prev;
        // remove buffer
        buf->prev->next = buf->next;
        buf->next->prev = buf->prev; 
        
        // change head pointer
        bcache.head->prev->next = buf;
        bcache.head->prev = buf;
        buf->next = bcache.head;
        bcache.head = buf;
    } 
}

char*
sstrcpy(char *s, const char *dst, int size)
{
    char *os;
    os = s;
    if (size <= 0)
        return os;
    while (size--) {
        *s++ = *dst++;
    }
    *s = '\0';
    return os;
}

void
test_buffer_1()
{
    binit ();
    init_disk ();
    print_disk ();
    struct CacheBuffer *cb;
    cb = bread(0, 8);
    char s[] = "Hello computer hello computer hello computer";
    sstrcpy(cb->data, s, sizeof(s));
    bwrite(cb);
    write_disk(2, "HHello world actually  hello hello computerello", 32);
    print_disk ();
}

int
main()
{
    test_buffer_1();
    //printf("%d\n", cb->valid);
    //printf("%d\n", cb->blockn);
    //cb = bcache.head;
    //int cnt = 0;
    //while (cnt != 20) {
    //    cb = cb->next;
    //    printf("%p\n", cb);
    //    cnt++;
    //}
    //printf("%d\n", cnt);
    //printf("Buffer data is %s\n", buf->data);
    //strcpy(buf->data, "MAC");//"Change string for what soever reason hello");
    //bwrite(buf);
    //print_disk ();
}

