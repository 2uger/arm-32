.syntax unified

.global swtch
swtch:
    add r0, r0, #8
    ldm r0, {r2, r3, r4, r5} // r0-r3
    ldr r6, [r0, #48] // r12
    ldr r7, [r0, #56] // lr
    ldr r8, [r0, #60] // pc
    ldr r9, [r0, #64] // psr
    ldr r1, [r0, #52] // sp

    // Store task's exception registers into it's own stack,
    // so cpu could pop them when return from exception
    stmdb r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

    // Restore all registers
    add r0, r0, #16
    ldm r0, {r4, r5, r6, r7, r8, r9}

    // Change stack
    msr MSP, r1
    bx r10

.global save_ctx
save_ctx:
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

    add r0, r0, #16
    stmia r0!, {r4, r5, r6, r7, r8, r9, r10, r11}

    // r12
    ldr r1, [sp, #20]
    str r1, [r0, #0]
    // sp
    mrs r1, MSP
    adds r1, #36
    str r1, [r0, #4]
    // lr
    ldr r1, [sp, #24]
    str r1, [r0, #8]
    // pc
    ldr r1, [sp, #28]
    str r1, [r0, #12]
    // ps
    ldr r1, [sp, #32]
    str r1, [r0, #16]

    bx lr


.global userret
userret:
    @ Prepare to execute task context
    ldr r2, [r0, #60] // sp 
    ldr r3, [r0, #68] // pc

    // Change user space stack pointer
    msr MSP, r2
    bx r3