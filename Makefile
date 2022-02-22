TOOLCHAIN = arm-none-eabi-
COMMON_FLAGS = -Ikernel/ -O0 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -c 

CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy

SRC = \
    uart.c \

OBJS = \
    entry.o \
    uart.o \

kernel: uart entry
	$(LD) -o kernel.elf -T link.ld $(OBJS) 
	rm *.o

main:
	$(CC) $(COMMON_FLAGS) $(SRC)

entry: 
	$(AS) -mcpu=cortex-m3 -g entry.S -o entry.o 

uart:
	$(AS) -mcpu=cortex-m3 -g uart.S -o uart.o 

help:
	echo $(OBJS)

clean:
	rm *.o *.elf

