// Simple file system
// Basic structure on disk:
// SPB :: INODES :: BITMAP :: BLOCKS

#include <stdint.h>

#include "buf.h"
#include "fs.h"
#include "defs.h"

struct spblock spb;

void
readspblock(uint32_t dev, struct spblock *spb)
{
    struct CacheBuffer *b;
    b = bget(dev, 0);
    mmemmove(spb, b->data, sizeof(*spb));
    brelease(b);
}

static void
zeroblock(uint32_t dev, uint32_t blockn)
{
    struct CacheBuffer *b;
    b = bget(dev, blockn);
    mmemset(b, 0, BLOCK_SIZE);
    bwrite(b);
    brelease(b);
}


// Functions to work with blocks on disk
// balloc - allocating block on disk
//          setup right bitmap bit
// bfree - actually just freeing bitmap bit

// allocating new block on disk
uint32_t
balloc(uint32_t dev)
{
    uint32_t m, b, bm;
    struct CacheBuffer *buf;

    for (b = 0; b < spb.size; b+=BPB) {
        // if block's size 8 => we get 64 bits as bitmap
        // get block of 8 * 8 bits showing status of blocks
        buf = bread(dev, BMBLOCK(b, spb));
        // iterating through byte till BPB or untill blocks amout on disk
        for (bm = 0; bm < BPB && bm + b < spb.size; bm++) {
            // actually we iterating through bits in byte(char)
            m = 1 << (bm % 8);
            if (buf->data[bm/8] & (m == 0)) { // is block free
                buf->data[bm/8] |= m; // mark block as not free
                bwrite(buf);
                brelease(buf);
                zeroblock(dev, b + bm);
                return b + bm; // block number that we allocate
            }
        }
        brelease(buf);
    }
    panic("out of disk block");
}

// freeing disk block
static void
bfree(uint32_t dev, uint32_t block_num) {
    // find bitmap bit for current block
    // make it 0
    struct CacheBuffer *b;
    b = bread(dev, (BMBLOCK(block_num, spb)));

    uint32_t bm = block_num % BPB;
    uint32_t m = 1 << (bm % 8);
    if (b->data[bm/8] & m == 0) // already free
        panic("freeing free block");

    // 000-1-000 -> 000-0-000
    b->data[bm/8] &= ~m;
    bwrite(b);
    brelease(b);
}

// Inodes code
//
// Simple example is:

// ialloc(int dev, int num) -- allocate fresh inode in disk
// iget(int dev, int num) -- return in memory copy of demanding inode
// ilock(struct inode* inode) -- locking in memory inode, so you can modify it
//                               read from memory if necessary

// In memory inodes
struct {
    // lock
    struct inode inode[INODES_PER_BLOCK];
} itable;

static struct inode* iget(uint32_t, uint32_t);

void
iinit(void)
{
    struct inode* in;
    for (in = &itable.inode[0]; in < &itable.inode[INODES_PER_BLOCK]; in++) {
    }
}

// allocating new inode on disk
struct inode*
ialloc(uint32_t dev, uint8_t type)
{
    struct CacheBuffer *b;
    struct dinode *din;

    for (uint32_t i = 1; i < spb.inodes_num; i++) {
        b = bread(dev, IBLOCK(i, spb));
        din = (struct dinode*)(b->data + i % INODES_PER_BLOCK);
        if (din->type == 0) {
            // TODO: Dont really know why zeroing only by size of pointer, not struct itself
            mmemset(din, 0, sizeof(*din));
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
iupdate(struct inode* in)
{
    struct CacheBuffer* b;
    struct dinode* dn;

    b = bget(in->dev, in->inum);
    dn = (struct dinode*)b->data + in->inum % INODES_PER_BLOCK;
    dn->type = in->type;
    dn->nlink = dn->nlink;
    dn->size = in->size;
    mmemmove(dn->addrs, in->addrs, sizeof(in->addrs));
    bwrite(b);
    brelease(b);
}


// return in memory inode
// if not find => return new one
// doesnt read from disk => valid = 0
// TODO: It won't work at least because there is not always the inode we really need
static struct inode*
iget(uint32_t dev, uint32_t inum)
{
    struct inode* in;

    for (in = &itable.inode[0]; in < &itable.inode[INODES_PER_BLOCK]; in++) {
        if (in->dev == dev && in->inum == inum) {
            in->ref++;
            return in;
        }
    }
}
//
// lock inode, read from disk if necessary
void
ilock(struct inode* in)
{
    struct CacheBuffer* buf;
    struct dinode* dn;

    if (in == 0 || in->ref == 0)
        panic("ilock: bad inode");

    if (in->valid == 0) {
        // read from disk
        buf = bread(in->dev, IBLOCK(in->inum, spb));
        dn = (struct dinode*)buf->data + in->inum % INODES_PER_BLOCK;
        in->type = dn->type;
        in->nlink = dn->nlink;
        in->size = dn->size;
        mmemmove(in->addrs, dn->addrs, sizeof(in->addrs));
        brelease(buf);
        in->valid = 1;
        if (in->type == 0)
            panic("ilock: inode got no type");
    }
}


//// unlcok inode
//void
//iunlock(struct inode *inode)
//{
//}
//
//
//// drop memory reference
//// if no more nlinks to inode => clean it up
//void
//iput(struct inode *ip)
//{
//
//}
//
