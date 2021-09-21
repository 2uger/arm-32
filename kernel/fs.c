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
    uint32_t m;
    struct CacheBuffer *buf;
    for (uint32_t b = 0; b < spb.size; b+=BPB) {
        // if block's size 8 => we get 64 bits as bitmap
        // get block of 8 * 8 bits showing status of blocks
        buf = bread(dev, BMBLOCK(b, spb));
        // iterating through byte till BPB or untill blocks amout on disk
        for (uint32_t bm = 0; bm < BPB && bm + b < spb.size; bm++) {
            // actually we iterating through bits in byte(char)
            m = 1 << (bm % 8);
            if (buf->data[bm/8] & m == 0) { // is block free
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
//
//// freeing disk block
//static void
//bfree(uint32_t dev, uint32_t block_num) {
//    // find bitmap bit for current block
//    // make it 0
//    struct buf *b;
//    b = bread(dev, (BMBLOCK(b, sb)));
//    uint32_t bm = block_num % BPB;
//    uint32_t m = 1 << (bm % 8);
//    if (b->data[bm/8] & m == 0) // already free
//        panic("freeing free block");
//    // 000-1-000 -> 000-0-000
//    b->data[bm/8] &= ~m;
//    bwrite(b);
//    brelease(b);
//}
//
//// Inodes code
//
//// In memory inodes
//struct {
//    // lock
//    struct inode inode[NINODES];
//} itable
//
//// allocating new inode on disk
//struct inode*
//ialloc(uint32_t dev, uint8_t type)
//{
//    struct buf *b;
//    struct dinode *din;
//    for (uint32_t i = 1; i < sb.inodes_num; i++) {
//        b = bread(dev, IBLOCK(i, sb));
//        din = (struct dinode*)(b->data + i % IPB);
//        if (din->type == 0) {
//            memset(din, 0, sizeof(*din));
//            din->type = type;
//            bwrite(b);
//            brelease(b);
//            return iget(dev, i);
//        }
//        brelease(b);
//    }
//    panic("no free inodes");
//}
//
//// copying in memory inode to disk
//void
//iupdate(struct inode* in)
//{
//    struct CacheBuffer *b;
//    struct dinode *dn;
//
//    b = bget(inode->dev, inode->inum);
//    dn = (struct dinode *)b->data + inode->inum&INODES_PER_BLOCK;
//    dn->type = in->type;
//    dn->nlink = dn->nlink;
//    dn->size = in->size;
//    mmemmove(dn->addrs, in->addrs, sizeof(in->addrs));
//    bwrite(b);
//    brelease(b);
//}
//
//
//// return in memory inode
//// if not find => return new one
//// doesnt read from disk => valid = 0
//static struct inode*
//iget(uint32_t dev, uint32_t inum)
//{
//}
//
//// lock inode, read from disk if necessary
//void
//ilock(struct inode *inode)
//{
//}
//
//
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
