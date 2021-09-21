// routine to switch from kernel space into user space
.global activate
activate:
    // save kernel state

    mrs ip, PSR
    push {r2, r3}

    msr PSP, r0
    //mrs r0, PSP
    mov r0, #3
    msr control, r0
    isb
    pop {r3}
    bx lr
    
    // first argument of calling activate is actually
    // address of user space stack
    //mov r1, #2
    //// change process state(thread-unprivilged)
    //msr CONTROL, r1

    //ldr r0, =0x21000000
    //msr PSP, r0
    //mrs r5, PSP
    //
    //mov r1, #1
    //msr CONTROL, r3

    //mrs r0, MSP
    //mrs r0, PSP
    //// instruction synchronization barrier
    //svc #3
    //// load user context
    ////pop {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    //bx lr

