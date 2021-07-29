// Simple file system
// Basic structure on disk:
// SPB -> INODES -> BITMAP -> BLOCKS
// Simple as that

#include "defs.h"
#include "param.h"
#include "fs.h"

void
readspblock(uint32_t dev, struct spblock *spb)
{
    struct buf *b;
    b = bget(dev, 0);
    mmemmove(spb, b->data, sizeof(*spb))
    brelease(b);
}

//static void
//zeroblock(uint32_t dev, uint32_t blockn)
//{
//    struct buf *b;
//    b = bget(dev, blockn);
//    memset(b, 0, BLOCK_SIZE);
//    bwrite(b);
//    brelease(b);
//}

// allocatin new block on disk
uint32_t
balloc(uint32_t dev)
{
    uint32_t m;
    struct buf *b;
    for (uint32_t b = 0; b < spb.size; b++) {
        // get block of 512 * 8 bits showing status of blocks
        b = bread(dev, BMBLOCK(b, sb));
        for (uint32_t bm = 0; bm < BPB < sb.size; bm++) {
            // actually we iterating through bits in byte(char)
            m = 1 << (bm % 8);
            if (b->data[bm/8] & m == 0) { // is block is free
                b->data[bm/8] |= m; // mark block as not free
                bwrite(b);
                brelease(b);
                return b + bm; // block number that we allocate
            }
        }
        brelease(b);
    }
    panic("out of disk block");
}

// free disk block
static void
bfree(uint32_t dev, uint32_t block_num) {
    // find bitmap bit for current block
    // make it 0
    struct buf *b;
    b = bread(dev, (BMBLOCK(b, sb));
    uint32_t bm = block_num % BPB;
    uint32_t m = 1 << (bm % 8);
    if (b->data[bm/8] & m == 0) // already free
        panic("freeing free block");
    // 0001000 -> 11101111
    b->data[bm/8] &= ~m;
    bwrite(b);
    brelease(b);
}

// Inodes code

// In memory inodes
struct {
    // lock
    struct inode inode[NINODES];
} itable

// allocating new inode on disk
struct inode*
ialloc(uint32_t dev, uint8_t type)
{
    struct buf *b;
    struct dinode *din;
    for (uint32_t i = 1; i < sb.inodes_num; i++) {
        b = bread(dev, IBLOCK(i, sb));
        din = (struct dinode*)(b->data + i % IPB);
        if (din->type == 0) {
            memset(din, 0, sizeof(*din));
            din->type = type;
            bwrite(b);
            brelease(b);
            return iget(dev, i);
        }
        brelease(b);
    }
    panic("no free inodes");
}

// copying in memory inode to disk
void
iupdate(struct inode*)
{
}


// return in memory inode
// if not find => return new one
// doesnt read from disk => valid = 0
static struct inode*
iget(uint32_t dev, uint32_t inum)
{
}

// lock inode, read from disk if necessary
void
ilock(struct inode *inode)
{
}


// unlcok inode
void
iunlock(struct inode *inode)
{
}

