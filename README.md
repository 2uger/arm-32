### Tiny OS
Simple operating system kernel for Cortex-M3 arch.<br> 
Simple thread preemptive scheduling by time interrupt.<br>
Kernel and user space division.<br>
### Environment
We actually need arm-none-eabi-... setup to run gcc, binutils and gdb<br>
Use Dockerfile to build image with all needed packages inside<br>
It helps to keep yours host system clean, appreciate that...
### How to use:
- Build container from Dockerfile.
    > **docker build -t arm-32 .**
- Run container with shared folder.
    > **docker run --name vision-kernel -v \`pwd\`:/vision -w /vision -i -t arm-32**
- Get inside container.
    > **docker exec -it vision-kernel bash**
- Start stopped container.
    > **docker start vision-kernel**
- Build kernel.
    > **make**
- Make qemu run our kernel.elf file and wait for gdb will connect to it.<br>lm3s6965evb - simple arm chip(cortex M3) with 64KB of RAM
    > **qemu-system-arm -M lm3s6965evb -kernel kernel.elf -nographic -s -S**
- To stop qemu.
    > **Ctrl-a x**
- Run gdb, select right arch and connect to qemu
    > **arm-none-eabi-gdb kernel.elf**  
    > **set architecture armv7**  
    > **target remote localhost:1234**
