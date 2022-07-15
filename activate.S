.global user_space_code
user_space_code:
    push {lr}
    bl input_loop
    pop {pc}

.global call_svc
call_svc:
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
    mov pc, r2

    bx lr
