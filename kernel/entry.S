.type entry, %function

vector_table:
    .word 0x0001000   // PC
    .word entry       // entry point
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler

.text
.global entry
entry:
    // Disable interrupts beside NMI and HardFault
    //mov r0, #0
    //msr PRIMASK, r0
    // Setup kernel stack
    ldr r0, =0x2001000
    msr MSP, r0
    b kernel_setup

    //movs r0, #0x0
    //msr BASEPRI, r0
    //msr CONTROL, r0 // Get into user mode

svc_handler:
    nop
