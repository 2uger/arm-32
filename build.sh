#!/bin/bash

# run qemu, wait and listen on localhost:1234
qemu-system-arm -M lm3s811evb -kernel kernel.elf -nographic -s -S

