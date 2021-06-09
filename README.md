### Run qemu with kernel to wait for gdb remote:
- qemu-system-arm -M lm3s811evb -kernel <kernel> -nographic -s -S 

### Run gdb remote
- 1. Setup architecture for armv7
- 2. Run: target remote localhost:1234

