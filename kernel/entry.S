.type entry, %function

vector_table:
    .word stack_top /* Вот это вершина стека */
    .word entry         /* А здесь инициализируем PC */
    .word nmi
    .word mem_fault
    .word bus_fault
    .word usage_fault
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word svc_handler
    .word sys_tick

.global entry
entry:
    // Disable interrupts beside NMI and HardFault
    mov r0, #0
    msr PRIMASK, r0
    // Setup kernel stack
    ldr r0, =KERNEL_SPACE_STACK
    msr MSP, r0
    b kernel_setup

    //movs r0, #0x0
    //msr BASEPRI, r0
    //msr CONTROL, r0 // Get into user mode

svc_handler:
    nop
