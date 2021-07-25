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
    intr_disable ();
    
    if (lck->lock)
        panic("Lock busy");
    lck->locks = 1;
}

void
release(struct lock *lck)
{
    lck->locks = 0;
    intr_enable ();
}
