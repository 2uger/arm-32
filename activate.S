.syntax unified

.global call_svc
call_svc:
    svc #0

.global swtch
swtch:
    // Store task's registers into it's own stack,
    // so cpu could pop them when return from exception
    add r0, r0, #8
    ldm r0, {r2, r3, r4, r5} // r0-r3
    ldr r6, [r0, #48] // r12
    ldr r7, [r0, #56] // lr
    ldr r8, [r0, #60]
    ldr r1, [r0, #52]
    ldr r9, =0x21000000

    stmdb r1!, {r2, r3, r4, r5, r6, r7, r8, r9}

    // Change stack
    msr MSP, r1
    bx lr
.global userret
userret:
    // r0 - pointer to task thread structure
    // r1 - pointer to kernel stack

    @ Save kernel context
    @ mrs r12, psr
    @ push {r2, r3, r4, r5, r6, r7, r8, r9, r10, r12, lr}
    @ str sp, [r1, #0]

    @ Prepare to execute task context
    ldr r2, [r0, #64] // sp 
    ldr r3, [r0, #68] // pc

    // Change user space stack pointer
    //msr MSP, r2
    pop {r2, pc}
    bx lr

.global firstret
firstret:
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
    pop {r2, r3, r4, r5, r6, r7, r8, r9, r10, r12, lr}
    msr psr, r12
    bx lr