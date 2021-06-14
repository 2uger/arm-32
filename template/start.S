.type entry, %function

.word stack_top /* Вот это вершина стека */
.word entry         /* А здесь инициализируем PC */
.word
.word
.word
.word
.word svc_handler
.word svc_handler
.word svc_handler
.word svc_handler
.word svc_handler
.word svc_handler

.global entry
entry:
    // Setup priviliged mode
    // Call main
    mrs r0, CONTROL // Check which mode we start executing
    movs r0, #0x1
    mrs r0, CONTROL // Check which mode we start executing
    ldr r0, =0x1000
    ldr r1, [r0] 
    msr PSP, r0
    msr MSP, r0
    mrs r0, PSP
    mrs r0, MSP
    movs r0, #0x1
    msr CONTROL, r0 // Get into privileged mode
    svc #0x3
    b main

svc_handler:
    nop
