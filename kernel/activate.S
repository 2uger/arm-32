// routine to switch from kernel space into user space
.global activate
activate:
    // save kernel state
    mov r3, r0
    mrs ip, PSR
    push {r2, r3, r4, r5, r6, r7, lr}

    // change user space stack address
    msr PSP, r0
    // change to user-thread mode
    mov r0, #3
    msr control, r0
    isb
    //svc #3

    ldm r1!, {r2, r3, r4, r5, r6, r7}
    ldr r0, [r1]
    mov pc, r0

    nop

//.section .user
.global user_start
user_start:
    mov r6, #0x1 
    svc #9
    

// function to save user process registers into 
// kernel structure
.global save_uregs
save_uregs:
    // r0 - start of struct
    stmia	r0!, {r2, r3, r4, r5, r6, r7}
    //mov pc, r1
    //str r1, [r0]
    bx lr
