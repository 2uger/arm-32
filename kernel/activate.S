// routine to switch from kernel space into user space
.global activate
activate:
    // save kernel state
    mrs ip, PSR
    //push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

    
    // first argument of calling activate is actually
    // address of user space stack
    msr PSP, r0
    mov r0, #3
    // change process state(thread-unprivilged)
    msr CONTROL, r0
    // instruction synchronization barrier
    isb
    svc #3
    // load user context
    //pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    bx lr

