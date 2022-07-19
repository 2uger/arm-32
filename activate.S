.syntax unified

.global swtch
swtch:
    // Store task's registers into it's own stack,
    // so cpu could pop them when return from exception
    add r0, r0, #8
    ldm r0, {r2, r3, r4, r5} // r0-r3
    ldr r6, [r0, #48] // r12
    ldr r7, [r0, #56] // lr
    ldr r8, [r0, #60] // pc
    ldr r9, [r0, #64] // psr
    ldr r1, [r0, #52] // sp

    stmdb r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

    add r0, r0, #16
    ldm r0, {r4, r5, r6, r7, r8, r9}

    // Change stack
    msr MSP, r1
    bx r10

.global save_ctx
save_ctx:
    // TODO: save whole context
    // Save interrupted thread context
    add r0, r0, #8
    // r0
    ldr r1, [sp, #4]
    str r1, [r0, #0]
    // r1
    ldr r1, [sp, #8]
    str r1, [r0, #4]
    // r2
    ldr r1, [sp, #12]
    str r1, [r0, #8]
    // r3
    ldr r1, [sp, #16]
    str r1, [r0, #12]

    str r4, [r0, #16]
    str r5, [r0, #20]
    str r6, [r0, #24]
    str r7, [r0, #28]
    str r8, [r0, #32]
    str r9, [r0, #36]
    str r10, [r0, #40]
    str r11, [r0, #44]

    // r12
    ldr r1, [sp, #20]
    str r1, [r0, #48]
    // sp
    mrs r1, MSP
    adds r1, #36
    str r1, [r0, #52]
    // lr
    ldr r1, [sp, #24]
    str r1, [r0, #56]
    // pc
    ldr r1, [sp, #28]
    str r1, [r0, #60]
    // ps
    ldr r1, [sp, #32]
    str r1, [r0, #64]

    bx lr


.global userret
userret:
    @ Prepare to execute task context
    ldr r2, [r0, #60] // sp 
    ldr r3, [r0, #68] // pc

    // Change user space stack pointer
    msr MSP, r2
    bx r3

.global kernelret
kernelret:
    // r0 - pointer to kernel stack
    msr MSP, r0
    //pop {r2, r3, r4, r5, r6, r7, r8, r9, r10, r12, lr}
    msr psr, r12
    bx lr