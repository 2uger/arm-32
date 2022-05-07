### Learning Cortex m3 CPU arch
Bootloader code to copy data and code into RAM.<br>
Thread pool with context switching and kernel-user space usage.
### Environment
We actually need arm-none-eabi-... setup to run gcc, binutils and gdb<br>
Use Dockerfile to build image with all needed packages inside<br>
It helps to keep yours host system clean, appreciate that...
### How to use:
- Build container from Dockerfile.
    > **docker build -t arm-32**
- Run container with shared folder.
    > **docker run --name vision-kernel -v `pwd`:/vision -w /vision -i -t arm-32**
- Get inside container.
    > **docker exec -it vision-kernel bash**
- Start stopped container.
    > **docker start vision-kernel**
- Build kernel.
    > **make**
- Make qemu run our kernel.elf file and wait for gdb will connect to it.<br>lm3s6965evb - simple arm chip with 64KB of RAM
    > **qemu-system-arm -M lm3s6965evb -kernel kernel.elf -nographic -s -S**
- To stop qemu.
    > **Ctrl-a x**
- Run gdb, select right arch and connect to qemu
    > **arm-none-eabi-gdb kernel.elf**  
    > **set architecture armv7**  
    > **target remote localhost:1234**
