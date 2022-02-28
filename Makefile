TOOLCHAIN = arm-none-eabi-
COMMON_FLAGS = -Ikernel/ -O0 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -c 

CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy

SRC = \
    main.c \
    uart.c \
    scheduler.c \

OBJS = \
    entry.o \
    main.o \
    uart.o \
    activate.o \
    scheduler.o \

kernel: main activate entry
	$(LD) -o kernel.elf -T link.ld $(OBJS) 
	rm *.o

main:
	$(CC) $(COMMON_FLAGS) $(SRC)

activate: 
	$(AS) -mcpu=cortex-m3 -g activate.S -o activate.o 

entry: 
	$(AS) -mcpu=cortex-m3 -g entry.S -o entry.o 

help:
	echo $(OBJS)

clean:
	rm *.o *.elf

