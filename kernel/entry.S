.type entry, %function

kernel_vector:
    .word 0x20001000   // Stack pointer
    .word entry       // entry point
    .word nmi_handler
    .word hardfault_handler
    .word memory_manag_fault
    .word bus_fault
    .word usage_fault
    .word 
    .word 
    .word svc_call
    .word svc_call
    .word svc_call
    .word svc_call
    .word svc_call
    .word svc_call
    .word svc_call
    .word 
    .word 
    .word pend_sv
    .word systick_handler
    .word systick_handler
    .word systick_handler
    .word systick_handler
    .word systick_handler
    .word systick_handler
    .word systick_handler
    .word systick_handler

.global entry
entry:
    // Disable interrupts beside NMI and HardFault
    mov r0, #0
    msr PRIMASK, r0
    // Setup kernel stack
    ldr r0, =0x20001000
    msr MSP, r0
    ldr r1, =kernel_setup
    bx r1
