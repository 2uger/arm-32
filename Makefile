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

OBJS = $(SRC:%.c=%.o)

train: echo $(OBJS)

kernel: $(LD) -o kernel.elf -T kernel/link.ld $(OBJS)

main:
	$(CC) $(COMMON_FLAGS) $(SRC)

initcode: $(AS) kernel/entry.S


help:
	echo $(OBJS)

clean:
	rm *.o

