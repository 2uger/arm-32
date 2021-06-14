#!/bin/sh

arm-as -c -mthumb -mlittle-endian -march=armv7-m -mcpu=cortex-m3 start.S -o start.o
arm-gcc -c -mthumb -ffreestanding -mlittle-endian -march=armv7-m -mcpu=cortex-m3 main.c -o main.o
arm-ld -T link.ld main.o start.o -o os.elf

qemu-system-arm -M lm3s811evb -kernel os.elf -nographic -s -S
