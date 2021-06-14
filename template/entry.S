.global entry
entry:
    // Setup priviliged mode
    // Call main
    mrs r0, CONTROL // Check which mode we start executing
    movs r0, #0x1
    msr CONTROL, r0 // Get into privileged mode
    mrs r0, CONTROL
    ldr r0, =KERNEL_SPACE_STACK
    str r0, [sp]
    b main

    
    
