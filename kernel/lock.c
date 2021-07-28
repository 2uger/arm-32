// Locks functions
// acquire -- disable interrupts and take a lock
// release -- release lock and enable interrupts

void
init_lock(struct lock *lck, char *name)
{
    lck->lock = 0;
    lck->name = name;
}

void
acquire(struct lock *lck)
{
    while (_set_and_test(&lck->lock, 1) == 1)
        ;
}

void
release(struct lock *lck)
{
    lck->lock = 0;
}


