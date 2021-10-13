// Simple file system
// Basic structure on disk:
// SPB :: INODES :: BITMAP :: BLOCKS

#include <stddef.h>
#include <stdint.h>

#include "buf.h"
#include "fs.h"
#include "defs.h"

#define min(a, b) (a < b ? a : b)

struct spblock spb;

// fun function to init fs by write superblock
void
init_fs(uint32_t dev)
{
    struct CacheBuffer *buf;
    int m = 9999; 
    buf = bread(dev, 0);
    mmemmove(buf->data, &m, 4);
    spb.magic = 9999;
    spb.size = BLOCKS_NUM * BLOCK_SIZE;
    spb.data_blocks_num = DATA_BLOCKS_NUM;
    spb.inodes_num = INODES_NUM;
    spb.inodes_start = 4;
    spb.bitmap_start = 7;

    bwrite(buf);
}

void
readspblock(uint32_t dev, struct spblock *spb)
{
    struct CacheBuffer *b;
    b = bget(dev, 0);
    kprintf("Read from first block %s\n", b->data);
    mmemmove(spb, b->data, sizeof(struct spblock));
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
// bfree - clean disk data block by setting bitmap bit into zero

// allocating new block on disk
uint32_t
balloc(uint32_t dev)
{
    uint32_t m, b, bm;
    struct CacheBuffer *buf;

    for (b = 1; b < spb.size; b+=BPB) {
        // if block's size 8 => we get 64 bits as bitmap
        // get block of 8*8 bits showing status of blocks
        buf = bread(dev, BMBLOCK(b, spb));
        kprintf("Read %d\n", BMBLOCK(b, spb));
        // iterating through byte till BPB or untill blocks amount on disk
        for (bm = 0; bm < BPB || bm + b < spb.size; bm++) {
            // actually we iterating through bits in byte(char)
            m = 1 << (bm % 8);
            if ((buf->data[bm/8] & m) == 0) { // is block free
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
//                             (create file actually)
// iget(int dev, int num) -- return in memory copy of demanding inode
//                           if no such inode -> process empty slot
// ilock(struct inode *inode) -- locking in memory inode, so you can modify it
//                               read from memory if necessary

// In memory inodes
struct {
    // lock
    struct inode inode[INODES_PER_BLOCK];
} itable;

// init in memory inodes data structure
void
iinit(void)
{
    struct inode *in;
    for (in = &itable.inode[0]; in < &itable.inode[INODES_PER_BLOCK]; in++) {
    }
}

// allocating new inode on disk
struct inode*
ialloc(uint32_t dev, uint8_t type)
{
    struct CacheBuffer *b;
    struct dinode *din;

    for (uint32_t i = 0; i < spb.inodes_num; i++) {
        int kkk = IBLOCK(i, spb);
        b = bread(dev, kkk);
        din = (struct dinode*)b->data + i % INODES_PER_BLOCK;
        if (din->type == 0) {
            mmemset(din, 0, sizeof(struct dinode));
            din->type = type;
            bwrite(b);
            brelease(b);
            return iget(dev, i);
        }
        brelease(b);
    }
    panic("no free inodes");
}

// copy in memory inode to disk
void
iupdate(struct inode *in)
{
    struct CacheBuffer *b;
    struct dinode *dn;

    kprintf("Num of inode is %d\n", IBLOCK(in->inum, spb));
    b = bget(in->dev, IBLOCK(in->inum, spb));
    dn = (struct dinode*)b->data + in->inum % INODES_PER_BLOCK;
    dn->type = in->type;
    dn->nlink = in->nlink;
    dn->size = in->size;
    mmemmove(dn->addrs, in->addrs, sizeof(in->addrs));
    bwrite(b);
    brelease(b);
}


// return in memory inode
// if not find => return new one
// doesnt read from disk => valid = 0
// TODO: It won't work at least because there is not always the inode we really need
struct inode*
iget(uint32_t dev, uint32_t inum)
{
    struct inode *in, *empty;

    empty = NULL;

    for (in = itable.inode; in < &itable.inode[INODES_PER_BLOCK]; in++) {
        if (in->ref > 0 && in->dev == dev && in->inum == inum) {
            in->ref++;
            return in;
        }
        if (in->ref == 0 && empty == NULL)
            empty = in;
    }
    if (empty == NULL)
        panic("iget: don't finding inode in memory");
    in = empty;
    in->dev = dev;
    in->inum = inum;
    in->ref = 1;
    in->valid = 0;
    return in;
}
//
// lock inode, read from disk if necessary
void
ilock(struct inode *in)
{
    struct CacheBuffer *buf;
    struct dinode *dn;

    if (in == NULL || in->ref == 0)
        panic("ilock: bad inode");

    kprintf("Inode num while ilock is %d\n", in->inum);
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

// unlcok inode
void
iunlock(struct inode *inode)
{
}

// truncate inode on disk
void
itrunc(struct inode *ip)
{
    for (uint32_t i = 0; i < DATA_BLOCKS_NUM; i++) {
        if (ip->addrs[i]) {
            bfree(ip->dev, i);
            ip->addrs[i] = 0;
        }
    }
}

// drop reference on inode in memory
// if that was last memory reference, recycle inode vacation in memory
// if no more dir links to inode on disk, free inode in memory and on disk
void
iput(struct inode *ip)
{
    if (ip->ref == 1 && ip->valid && ip->nlink == 0) {
        itrunc(ip);
        ip->type = 0;
        iupdate(ip);
        ip->valid = 0;
    }
    ip->ref--;
}


// inode content
// return block number in file system by 
// block number in current inode
uint32_t
bmap(struct inode *in, uint32_t bn)
{
    uint32_t addr;
    if ((addr = in->addrs[bn]) == 0)
        in->addrs[bn] = addr = balloc(in->dev);
    kprintf("Address is %d\n", addr);
    return addr;
}

// read information from inode 
// off - offset
// n   - size of information to read
uint32_t
readi(struct inode *in, uint32_t dst_addr, uint32_t off, uint32_t n)
{
    // how many bytes read
    uint32_t tot;
    // offset in current block
    uint32_t m;
    struct CacheBuffer *buf;

    if (off > in->size)
        return 0;
    if (off + n > in->size)
        n = in->size - off;

    for (tot = 0; tot < n; tot += m, off += m, dst_addr += m) {
        kprintf("Get buffer for readi\n");
        buf = bread(in->dev, bmap(in, off / BLOCK_SIZE));
        kprintf("%s\n", buf->data);

        m = min(n - tot, BLOCK_SIZE - off % BLOCK_SIZE);
        // copy data to dst addrs
        mmemmove(dst_addr, buf->data, m);
    }
}


uint32_t
writei(struct inode *in, uint32_t src_addr, uint32_t off, uint32_t n)
{
    kprintf("Size of inode %d,  %d\n", in->size, in->inum);
    uint32_t tot;
    uint32_t m;
    struct CacheBuffer *buf;

    if (off > in->size || n < 0)
        return -1;
    // impossible to read more than all filesystem have
    if (off + n > DATA_BLOCKS_NUM * BLOCK_SIZE)
        return -1;

    for (tot = 0; tot < n; tot += m, off += m, src_addr += m) {
        // iterate through inode data blocks, that inode
        // store in addrs field
        kprintf("Get buffer for writei\n");
        buf = bread(in->dev, bmap(in, off / BLOCK_SIZE));
        // first case is when we stop reading from somewhere inside block
        m = min(n - tot, BLOCK_SIZE - off % BLOCK_SIZE);
        mmemmove(buf->data, src_addr, m);
        // put buffer into disk with new data
        bwrite(buf);
        brelease(buf);
    }
    // means write more data to end of file or rewrite part of that
    in->size = (off > in->size) ? off : in->size;
    kprintf("Size of inode %d,  %d\n", in->size, in->inum);
    iupdate(in);
    return tot;
}

// as for now, we dont have directory hierarchy, because just want to test
// simple inodes with file names and one directory, that store all of them
struct inode*
dirlookup(struct inode *dir, char *filename)
{
    struct dirent *de;

    if (dir->type != DIRECTORY)
        panic("dirlookup: directory inode has wrong type");
    
    for (uint32_t off = 0; off < dir->size; off += sizeof(struct dirent)) {
        readi(dir, de, off, sizeof(struct dirent));
        if (sstrcmp(de->name, filename, MAX_FILE_NAME)) {
            return iget(0, de->inum);
        }
    }
    return 0;
}

// add new entry in directory
uint32_t
dirlink(struct inode *dir, char *name, uint32_t inum)
{
    uint32_t off;
    struct dirent *de;
    struct inode *in;

    kprintf("Size of inode %d,  %d\n", dir->size, dir->inum);
    if ((in = dirlookup(dir, name)) != 0) {
        iput(in);
        return -1;
    }
    for (off = 0; off < dir->size; off += sizeof(struct dirent)) {
        if (readi(dir, de, off, sizeof(struct dirent)) != sizeof(struct dirent))
            panic("dirlink: bad entry in directory");
        if (de->inum == 0)
            break;
    }
    mmemmove(de->name, name, 2);
    de->inum = inum;
    kprintf("Size of inode %d,  %d\n", dir->size, dir->inum);
    if (writei(dir, de, off, sizeof(struct dirent)) != sizeof(struct dirent))
        panic("dirlink: can't write new entry to dir");

    return 0;
}
