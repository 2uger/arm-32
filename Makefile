TOOLCHAIN = arm-none-eabi-
COMMON_FLAGS = -Ikernel/ -O0 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -c 

CC = $(TOOLCHAIN)gcc
AS = $(TOOLCHAIN)as
LD = $(TOOLCHAIN)ld
OBJCOPY = $(TOOLCHAIN)objcopy

K = kernel
U = user

SRC = \
    $K/console.c \
    $K/isr.c \
    $K/proc.c \
    $K/setup.c \
	$K/string.c \
	$K/panic.c \
    $K/uart.c \
    $K/disk_emulate.c \
    $K/buf.c \
    $K/fs.c \
    $K/sysfile.c \
    $K/sys_call.c \
    $K/test.c 

OBJS = \
    entry.o \
	activate.o \
    console.o \
    isr.o \
    proc.o \
    setup.o \
    panic.o \
	string.o \
    uart.o \
    disk_emulate.o \
    buf.o \
    fs.o \
    sysfile.o \
    sys_call.o \
    test.o \

kernel: main initcode activate
	$(LD) -o kernel.elf -T kernel/link.ld $(OBJS) 
	rm *.o

main:
	$(CC) $(COMMON_FLAGS) $(SRC)

activate:
	$(AS) -mcpu=cortex-m3 kernel/activate.S -o activate.o 
    

initcode: 
	$(AS) -mcpu=cortex-m3 kernel/entry.S -o entry.o 

help:
	echo $(OBJS)

clean:
	rm *.o *.elf

