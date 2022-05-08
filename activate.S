.global user_space_code
user_space_code:
    push {lr}
    bl input_loop
    pop {pc}

.global print
print:
    push {lr}
    svc #0
    pop {pc}

.global activate
activate:
    // r0 - pointer to Thread structure
    ldr r1, [r0, #40] // sp 
    ldr r2, [r0, #32] // pc

    // Change user space stack pointer
    msr PSP, r1

    // Change control register to get into Thread User mode
    mov r3, #3
    msr CONTROL, r3

    mov pc, r2
