TOOLCHAIN = arm-
COMMON_FLAGS = -Ikernel/ -O2 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -c

CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy

K = kernel
U = user

SRC = \
    $K/console.c \
    $K/core_cm3.c \
    $K/isr.c \
    $K/main.c \
    $K/proc.c \
    $K/setup.c \
    $K/uart.c 

OBJS = \
    entry.o \
    console.o \
    core_cm3.o \
    isr.o \
    main.o \
    proc.o \
    setup.o \
    uart.o \

kernel: main initcode
	$(LD) -o kernel.elf -T kernel/link.ld $(OBJS) 
	rm *.o


main:
	$(CC) $(COMMON_FLAGS) $(SRC)

initcode: 
	$(AS) -mcpu=cortex-m3 kernel/entry.S -o entry.o 

help:
	echo $(OBJS)

clean:
	rm *.o *.elf

