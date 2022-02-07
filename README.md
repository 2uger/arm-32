### Environment
We actually need arm-none-eabi-... setup to run gcc, binutils and gdb
Use Dockerfile to build image with all needed packages inside
That is how Docker helps avoid packages inside host system, kinda cool...
### How to use:
* **make**
    build kernel
* **qemu-system-arm -M lm3s6965evb -kernel kernel.elf -nographic -s -S**
    make qemu run our kernel.elf file and wait for gdb will connect to it
    lm3s6965evb - simple arm chip with 64KB of RAM
* **arm-none-eabi-gdb** -> **set architecture armv7** -> **target remote localhost:1234**
    run gdb, select right arch and connect to qemu
