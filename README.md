### What is Vision?
Basically it's super light and simple kernel for Cortex m3 CPU
Mostly to write basic concepts in OS(threads, context switching, memory management...)

### How to use?
### Run qemu with kernel to wait for gdb remote:
- qemu-system-arm -M lm3s811evb -kernel kernel.elf -nographic -s -S 

### Run gdb remote
- 1 Setup architecture for armv7
- 2 Run: target remote localhost:1234
