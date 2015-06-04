#ifndef __BUF_H
#define __BUF_H

#define B_BUSY  0x1 // buffer is locked
#define B_VALID 0x2 // has been read form disk
#define B_DIRTY 0x4 // need to be written to disk

#define NBUF 128    // size of disk buffer cache
struct buf {
    char flags;     // B_BUSY B_VALID B_DIRTY
    char dev;       // only one disk, dev = 0
    uint32_t lba;   // linear block address = sector number
    struct buf *prev;   // LRU Cache List 双向
    struct buf *next;
    struct buf *qnext;  // 磁盘操作请求队列, 单向
    char data[512];
};

#endif