### Vision OS
Tired of complex af systems?
Believe that it's all about simple and beatiful stuff?
Minimalism in action!!!

### What is Vision?
Basically it's super light kernel for Cortex m3 CPU
### Why is that?
- Super clean and understandble code
- Simple, but clean code techincs

### How to use?
### Run qemu with kernel to wait for gdb remote:
- qemu-system-arm -M lm3s811evb -kernel kernel.elf -nographic -s -S 

### Run gdb remote
- 1 Setup architecture for armv7
- 2 Run: target remote localhost:1234

### TODO:
- Run this code, try to call first system call from user space
- Write normal printf function
