.type entry, %function

kernel_vector:
    .word 0x0001000   // PC
    .word entry       // entry point
    .word nmi_handler
    .word hardfault_handler

.global entry
entry:
    // Disable interrupts beside NMI and HardFault
    //mov r0, #0
    //msr PRIMASK, r0
    // Setup kernel stack
    ldr r0, =0x2001000
    msr MSP, r0
    ldr r1, =kernel_setup
    bx r1

    //movs r0, #0x0
    //msr BASEPRI, r0
    //msr CONTROL, r0 // Get into user mode

nmi_handler:
    nop

hardfault_handler:
    nop

svc_handler:
    nop
