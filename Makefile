TOOLCHAIN = arm-none-eabi-
COMMON_FLAGS = -Ikernel/ -O2 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -c -g

CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy

SRC = \
    console.c \
    scheduler.c \
    user.c \
    timer.c \
    interrupts.c \
    syscall.c \
    string.c \
    setup.c

OBJS = \
    entry.o \
    isr.o \
    console.o \
    activate.o \
    user.o \
    scheduler.o \
    timer.o \
    interrupts.o \
    syscall.o \
    string.o \
    setup.o

kernel: main activate entry isr
	$(LD) -o kernel.elf -T link.ld $(OBJS) 
	rm *.o

main:
	$(CC) $(COMMON_FLAGS) $(SRC)

activate: 
	$(AS) -mcpu=cortex-m3 -g activate.S -o activate.o 

entry: 
	$(AS) -mcpu=cortex-m3 -g entry.S -o entry.o 

isr: 
	$(AS) -mcpu=cortex-m3 -g isr.S -o isr.o 

help:
	echo $(OBJS)

clean:
	rm *.o *.elf

