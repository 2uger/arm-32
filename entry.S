.type entry, %function

kernel_vector:
    .word 0x20001000   // Stack pointer
    .word entry       // entry point
    .word nmi_handler
    .word hardfault_handler
    .word memory_manag_fault_handler
    .word bus_fault_handler
    .word usage_fault_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
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

//copy_data_to_ram:
//    .extern _kernel_base
//    ldr r0, =_kernel_base
//    ldr r1, = 0x20000000
//    .extern _kernel_end
//    ldr r2, = _kernel_end
//copy_loop:
//    ldr r3, [r0]
//    str r3, [r1]
//    add r0, r0, #0x4
//    add r1, r1, #0x4
//    cmp r1, r2
//    blt copy_loop

//zero_bss:
//    movs r0, #0x00000000
//    .extern _ebss
//    ldr r2, =_ebss
//zero_bss_loop:
//    str r0, [r1]
//    add r1, r1, #0x4
//    cmp r1, r2
//    blt zero_bss_loop
//    bx lr
