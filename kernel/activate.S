// routine to switch from kernel space into user space
.global activate
activate:
    // save kernel state
    push {}
    
    msr psp, r0
    mov r0, #3
    msr control, r0

    // load user context
    pop {}
    bx lr

