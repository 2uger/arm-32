#ifndef LOCK_H
#define LOCK_H

struct lock {
    uint16_t lock;
    
    char *name; // for debugging purpose
};

#endif
