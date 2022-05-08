void
irq_off(void)
{
    __asm__("cpsid i");
}

void
irq_on(void)
{
    __asm__("cpsid i");
}