.global print_char
print_char:
    ldr r1, =0x4000c000
    str r0, [r1]
    bx lr
