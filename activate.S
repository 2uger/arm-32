.global activate
activate:
    // r0 - pointer to Thread structure
    push {lr}
    ldr r1, [r0, #8] // pc
    ldr r2, [r0, #12] // sp
    mov r3, #3
    msr PSP, r2
    msr CONTROL, r3
    mov pc, r1

.global user_space_code
user_space_code:
    ldr r0, =0x41
    ldr r0, =0x0D
    svc #9
    ldr r1, =0x0D
