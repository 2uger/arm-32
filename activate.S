.global user_space_code
user_space_code:
    .extern greetings
    push {lr}
    ldr r0, =greetings
    svc #1
    pop {r1}
    bx r1

.global activate
activate:
    // r0 - pointer to Thread structure
    push {lr}
    ldr r1, [r0, #8] // sp 
    ldr r2, [r0, #12] // pc
    msr PSP, r1
    mov r3, #3
    msr CONTROL, r3
    mov pc, r2
