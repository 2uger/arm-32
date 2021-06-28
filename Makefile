
TOOLCHAIN = arm-
COMMON_FLAGS = -O2 -nostdlib -nostartfiles -ffreestanding -Wall -mthumb -mcpu=cortex-m3 -c

help:
	echo "Compile whole bootloader"

bootloader: system_init.o main.o boot.o platform.o uart.o
	$(TOOLCHAIN)ld -o bootloader.elf -T memory_layout.ld system_init.o main.o boot.o platform.o

system_init.o:
	$(TOOLCHAIN)gcc -c -I. system_init.c -o system_init.o

main.o:
	$(TOOLCHAIN)gcc -c -I. ../main.c -o main.o

boot.o:
	$(TOOLCHAIN)as platform/boot.s -o boot.o

uart.o:
	$(TOOLCHAIN)gcc $(COMMON_FLAGS) -Iplatform/ -Icmsis/ platform/uart.c -o uart.o

timer.o:
	$(TOOLCHAIN)gcc $(COMMON_FLAGS) -Ipl


led_driver.o:
