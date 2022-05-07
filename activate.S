.global user_space_code
user_space_code:
    push {lr}
    bl input_loop
    pop {pc}

.global print
print:
    svc #3
    bx lr

.global activate
activate:
    // r0 - pointer to Thread structure
    ldr r1, [r0, #8] // sp 
    ldr r2, [r0, #12] // pc
    // Change user space stack pointer
    msr PSP, r1
    mov r3, #3
    // Change control register to get into Thread User mode
    msr CONTROL, r3
    mov pc, r2
